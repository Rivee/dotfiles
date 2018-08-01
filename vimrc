" Config of vim


set number      " Affiche les numéros de ligne
set smartindent " Indentation intelligente
set autoindent  " Conserve l'indentation sur une nouvelle ligne
set cursorline
set encoding=utf-8
set ruler " Affiche la position du curseur
set tabstop=4
set shiftwidth=4
set expandtab
syntax on

set colorcolumn=80

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'vim-airline/vim-airline'
Plugin 'jiangmiao/auto-pairs'
Plugin 'NLKNguyen/papercolor-theme'
Plugin 'Valloric/YouCompleteMe'
Plugin 'wikitopian/hardmode'
Plugin 'tomasr/molokai'
Plugin 'szorfein/darkest-space'
Plugin 'fugalh/desert.vim.git'
Plugin 'scrooloose/nerdtree'
Plugin 'vim-syntastic/syntastic'
Plugin 'dylanaraps/wal'
Plugin 'tyrannicaltoucan/vim-deep-space'
Plugin 'flazz/vim-colorschemes'
call vundle#end()

map <C-n> :NERDTreeToggle<CR>
nnoremap <F5> :tabprevious<CR>
nnoremap <F6> :tabnext<CR>
nmap <S-Enter> O<Esc>
nmap <CR> o<Esc>

filetype plugin indent on
highlight ExtraWhitespace ctermbg=white
set background=dark
colorscheme PaperColor
