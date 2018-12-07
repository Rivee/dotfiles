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
Plugin 'romainl/vim-qf'
Plugin 'vim-scripts/DoxygenToolkit.vim'
Plugin 'NLKNguyen/papercolor-theme'
Plugin 'wikitopian/hardmode'
Plugin 'flazz/vim-colorschemes'
call vundle#end()

nnoremap <F5> :tabprevious<CR>
nnoremap <F6> :tabnext<CR>
nmap <S-Enter> O<Esc>
nmap <CR> o<Esc>

set clipboard=unnamed

set list
set listchars=tab:>─,eol:$,trail:\ ,nbsp:¤
set fillchars=vert:│

filetype plugin indent on
highlight ExtraWhitespace ctermbg=white
set background=dark
colorscheme PaperColor
