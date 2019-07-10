#include "../comps.h"
#include "../utils.h"


enum status {
    CHARGING,
    DISCHARGING,
    UNKNOWN,
    FULL,
};

struct batt_info {
    int full_charge;
    int full_design_charge;
    int current_charge;
    int ream_charge;
    int present_r;
    
    int secs_ream;
    float percentage_rem;
    enum status st;
};

static void to_val(char **st) 
{
    while (**st != '=')
        (*st)++;
}


static int get_batt_info(struct batt_info *batt, char *path) 
{
    FILE *file = open_file(path);


    char *val = NULL;
    char *line = NULL;
    size_t size = 0;
    while (line = readline(file, &size)) {
        val = line;
        to_val(&val);
        if (BEGINS_WITH(line, "POWER_SUPPLY_ENERGY_NOW=")) {
            batt->ream_charge = atoi(val + 1);
            batt->percentage_rem = -1;
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_POWER_NOW=")) {
            batt->present_r = atoi(val + 1);
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_STATUS=Discharging")) {
            batt->st = DISCHARGING;
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_STATUS=Charging")) {
            batt->st = CHARGING;
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_STATUS=Full")) {
            batt->st = FULL;
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_STATUS=")) {
            batt->st = UNKNOWN;
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_ENERGY_FULL_DESIGN=")) {
            batt->full_design_charge = atoi(val + 1);
        } else if (BEGINS_WITH(line, "POWER_SUPPLY_ENERGY_FULL=")) {
            batt->full_charge = atoi(val + 1);
        }
    }
    fclose(file);
    return 1;
}

static void add_batt_info(struct batt_info *dst, struct batt_info *src)
{
    dst->full_design_charge += src->full_design_charge;
    dst->full_charge += src->full_charge;
    dst-> ream_charge += src->ream_charge;

    if (dst->st == DISCHARGING) {
        dst->present_r *= -1;
    }

    if (src->st == DISCHARGING) {
        dst->present_r += src->present_r * -1;
    } else
        dst->present_r += src->present_r;

    if (dst->st == UNKNOWN)
        dst->st = src->st;
    else if (dst->st == DISCHARGING) {
        if (dst->present_r > 0)
            dst->st = CHARGING;
    } else if (dst->st == CHARGING) {
        if (dst->present_r < 0)
            dst->st = DISCHARGING;
    } else if (dst->st == FULL) {
        if (src->st != UNKNOWN)
            dst->st = src->st;
    }

    dst->present_r = abs(dst->present_r);
}


static struct batt_info* get_all_battery()
{
    struct batt_info *b_res = calloc(1, sizeof(struct batt_info));
    struct batt_info *b_temp = calloc(1, sizeof(struct batt_info));


    get_batt_info(b_res, "/sys/class/power_supply/BAT0/uevent");
    get_batt_info(b_temp, "/sys/class/power_supply/BAT1/uevent");
    add_batt_info(b_res, b_temp);
    free(b_temp);
    return b_res;
}

char* get_output_batt_all()
{
    struct batt_info *b = get_all_battery();
    b->percentage_rem = 
        (((float)b->ream_charge / (float)b->full_charge) * 100);
    if (b->percentage_rem > 100)
        b->percentage_rem = 100;
    if (b->present_r > 0 && b->st != FULL) {
        if (b->st == CHARGING)
            b->secs_ream = 3600.0 *
                (b->full_charge - b->ream_charge) / b->present_r;
        else if (b->st == DISCHARGING)
            b->secs_ream = 3600.0 * b->ream_charge / b->present_r;
    }

    char *res = calloc(50, sizeof(char));

    char st[10] = {0};
    switch (b->st) {
        case CHARGING :
            strcpy(st, "+");
            break;
        case DISCHARGING :
            strcpy(st, "-");
            break;
        case FULL :
            strcpy(st, "~");
    }

    int hours = 0, secs = 0, min = 0;
    
    hours = b->secs_ream / 3600;
    secs = b->secs_ream - (hours * 3600);
    min = secs / 60;
    secs -= (min * 60);

    sprintf(res, "%s %.2f%% %02d:%02d:%02d", 
            st, b->percentage_rem, hours, min, secs);


    return res;
}

char *get_state(char *battery)
{
    char path[PATH_MAX] = {0};
    sprintf(path, "/sys/class/power_supply/%s/status", battery);
    
    FILE *file = fopen(path, "r");
    if (!file) {
        err(1, "Fail fopen : %s ", strerror(errno));
        return NULL;
    }

    char status[50] = {0};
    if (!fgets(status, 50, file)) {
        err(1, "Fail fgets : %s ", strerror(errno));
        return NULL;
    }

    if (!strcmp(status, "Discharging\n")) {
        return "-";
    }
    else if (!strcmp(status, "Charging\n")) {
        return "+";
    }
    else
        return NULL;
}

char* get_perc_all()
{
    char path_bat0[PATH_MAX] = {0};
    char path_bat1[PATH_MAX] = {0};


    FILE * file_bat0 = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (!file_bat0) {
        err(1, "Fail fopen : %s ", strerror(errno));
        return NULL;
    }
    FILE * file_bat1 = fopen("/sys/class/power_supply/BAT1/capacity", "r");
    if (!file_bat1) {
        err(1, "Fail fopen : %s ", strerror(errno));
        return NULL;
    }

    char cap_bat0[10] = {0};
    char cap_bat1[10] = {0};

    fgets(cap_bat0, 10, file_bat0);
    fgets(cap_bat1, 10, file_bat1);

    int perc_bat0 = 0, perc_bat1 = 0;

    sscanf(cap_bat0, "%d\n", &perc_bat0);
    sscanf(cap_bat1, "%d\n", &perc_bat1);

    float perc = (perc_bat0 + perc_bat1) / 2;

    char *res = calloc(10, sizeof(char));
    
    sprintf(res, "%.1f", perc);

    return res;
}
