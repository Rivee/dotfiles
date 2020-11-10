" Custom Vim Config
set number
set smartindent
set autoindent
set encoding=utf-8

set textwidth=79 " Limit the text to 80 chars

set ruler
set tabstop=8
syntax on
set cc=80
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'joshdick/onedark.vim'

" Theme / Colosheme

" Helpers
Plugin 'romainl/vim-qf'
Plugin 'tpope/vim-fugitive'
Plugin 'ludovicchabant/vim-gutentags'
Plugin 'ntpeters/vim-better-whitespace'
Plugin 'rust-lang/rust.vim'
Plugin 'rhysd/vim-clang-format'
Plugin 'tpope/vim-vinegar'

call vundle#end()

filetype plugin indent on

set background=dark
colorscheme delek

set list
set listchars=tab:>\ ,eol:¬,trail:\ ,nbsp:¤

hi Special cterm=NONE ctermfg=DarkYellow
hi Statement cterm=Bold ctermfg=Yellow
hi Comment cterm=NONE ctermfg=DarkCyan
hi Type cterm=Bold ctermfg=Cyan

set path+=**
set wildmenu

let g:netrw_banner=0

" Resize automatically the size of windows split
autocmd VimResized * wincmd =
