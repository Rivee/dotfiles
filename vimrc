" Config of vim

set number      " Affiche les numéros de ligne
set smartindent " Indentation intelligente
set autoindent  " Conserve l'indentation sur une nouvelle ligne
set cursorline

set encoding=utf-8
set ruler " Affiche la position du curseur
set tabstop=8

" Space identation
set shiftwidth=4
set expandtab

set textwidth=80

syntax on

set colorcolumn=80
set updatetime=100

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'

" Theme / Colosheme
Plugin 'vim-airline/vim-airline'
Plugin 'calincru/flex-bison-syntax'

" Helpers
Plugin 'romainl/vim-qf'
Plugin 'tpope/vim-fugitive'
Plugin 'ludovicchabant/vim-gutentags'
Plugin 'ntpeters/vim-better-whitespace'
Plugin 'airblade/vim-gitgutter'
Plugin 'rhysd/vim-clang-format'
Plugin 'tpope/vim-vinegar'

call vundle#end()

filetype plugin indent on

set list
set listchars=tab:>\ ,eol:¬,trail:\ ,nbsp:¤
set background=dark

set t_md=
hi def cCustomFunc  gui=NONE
hi def cCustomClass  gui=NONE
