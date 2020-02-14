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
Plugin 'morhetz/gruvbox'
Plugin 'w0ng/vim-hybrid'
Plugin 'nanotech/jellybeans.vim'

" Helpers
Plugin 'jiangmiao/auto-pairs'
Plugin 'romainl/vim-qf'
Plugin 'tpope/vim-fugitive'
Plugin 'vim-scripts/DoxygenToolkit.vim'
Plugin 'ludovicchabant/vim-gutentags'
Plugin 'ntpeters/vim-better-whitespace'
Plugin 'tpope/vim-vinegar'
Plugin 'airblade/vim-gitgutter'
Plugin 'ziglang/zig.vim'

" Mics
Plugin 'wikitopian/hardmode'
call vundle#end()

nnoremap <F5> :tabprevious<CR>
nnoremap <F6> :tabnext<CR>
nmap <S-Enter> O<Esc>
nmap <CR> o<Esc>

set term=st-256color
set clipboard=unnamed
set list
set listchars=tab:>\ ,eol:¬,trail:\ ,nbsp:¤

filetype plugin indent on
highlight ExtraWhitespace ctermbg=white
hi CursorLine term=bold cterm=bold guibg=Grey40

set background=dark
