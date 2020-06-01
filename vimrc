set number
set smartindent
set autoindent
" set cursorline

set encoding=utf-8
set ruler
set tabstop=8

set expandtab
set shiftwidth=4

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
Plugin 'CohenArthur/tiger-vim'
Plugin 'w0ng/vim-hybrid'
Plugin 'zefei/simple-dark'
Plugin 'joshdick/onedark.vim'
Plugin 'altercation/vim-colors-solarized'

" Helpers
Plugin 'romainl/vim-qf'
Plugin 'tpope/vim-fugitive'
Plugin 'vim-scripts/DoxygenToolkit.vim'
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

set spelllang=en

" Resize automatically the size of windows split
autocmd VimResized * wincmd =
