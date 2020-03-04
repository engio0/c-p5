set langmenu=en_US.UTF-8
language messages en_US.UTF-8

set encoding=utf-8
set termencoding=utf-8
set hlsearch
set number
set autoindent
set expandtab
set scrolloff=2
set wildmode=longest,list
set autowrite
set autoread
set cindent
set bs=eol,start,indent
set history=256
set laststatus=2
"set paste
set shiftwidth=4
set showmatch
set smartcase
set smarttab
set showcmd
set smartindent
set softtabstop=4
set tabstop=4
set backspace=indent,eol,start
set ruler
set incsearch
set ignorecase
set statusline=\ %<%l/%L:%v\ [%P]%=%a\ %h%m%r\ %F\
syntax enable
set lines=50 columns=120
set path+=**
set wildmenu

" moves cursor to the last modified position
au BufReadPost *
\ if line("'\"") > 0 && line("'\"") <= line("$") |
\ exe "norm g`\"" |
\ endif

set noimd

"new status line experiment...
hi User1 ctermfg=0    ctermbg=15   guifg=#ffdad8  guibg=#880c0e
hi User2 ctermfg=15   ctermbg=4    guifg=#000000  guibg=#F4905C
hi User3 ctermfg=0    ctermbg=7    guifg=#292b00  guibg=#f4f597
hi User4 ctermfg=0    ctermbg=8    guifg=#112605  guibg=#aefe7B
hi User5 ctermfg=15   ctermbg=12   guifg=#051d00  guibg=#7dcc7d
hi User7 ctermfg=15   ctermbg=14   guifg=#ffffff  guibg=#880c0e gui=bold
hi User8 ctermfg=0    ctermbg=11   guifg=#ffffff  guibg=#5b7fbb
hi User9 ctermfg=0    ctermbg=13   guifg=#ffffff  guibg=#810085
hi User0 ctermfg=15   ctermbg=2    guifg=#ffffff  guibg=#094afe
set statusline=
set statusline+=%7*\[%n]                                  "buffernr
set statusline+=%1*\ %<%F\                                "File+path
set statusline+=%2*\ %y\                                  "FileType
set statusline+=%3*\ %{''.(&fenc!=''?&fenc:&enc).''}      "Encoding
set statusline+=%3*\ %{(&bomb?\",BOM\":\"\")}\            "Encoding2
set statusline+=%4*\ %{&ff}\                              "FileFormat (dos/unix..)
set statusline+=%5*\ %{&spelllang}\%{HighlightSearch()}\  "Spellanguage & Highlight on?
set statusline+=%8*\ %=\ row:%l/%L\ (%03p%%)\             "Rownumber/total (%)
set statusline+=%9*\ col:%03c\                            "Colnr
set statusline+=%0*\ \ %m%r%w\ %P\ \                      "Modified? Readonly? Top/bot.

function! HighlightSearch()
  if &hls
    return 'H'
  else
    return ''
  endif
endfunction

"==================== Vundle Starts ====================
set nocompatible              " be iMproved, required
filetype off                  " required
set rtp+=$HOME/.vim/bundle/Vundle.vim/
call vundle#begin('$HOME/.vim/bundle/')

Plugin 'VundleVim/Vundle.vim' " let Vundle manage Vundle, required

"Plugin 'tpope/vim-fugitive'
"Plugin 'valloric/youcompleteme'
Plugin 'Valloric/YouCompleteMe'
Plugin 'Valloric/ListToggle'
"Plugin 'scrooloose/nerdtree'
"Plugin 'tpope/vim-surround'
"Plugin 'scrooloose/syntastic'
Plugin 'altercation/vim-colors-solarized'
"Plugin 'kien/ctrlp.vim'
Plugin 'vim-airline/vim-airline'
"Plugin 'easymotion/vim-easymotion'
"Plugin 'junegunn/fzf.vim'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'lervag/vim-foam'

call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
"====================  Vundle Ends  ====================

if (&term == "builtin_gui" || has("gui_running"))
    set background=dark
    colorscheme solarized
    set guifont=NanumGothicCoding:h12:cHANGEUL
"    set guifont=Consolas:h11:cANSI
"    set guifontwide=NanumGothicCoding:h11:cDEFAULT
endif
  
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/.ycm_extra_conf.py'
let g:ycm_autoclose_preview_window_after_completion = 0
let g:ycm_autoclose_preview_window_after_insertion = 1
let g:ycm_always_populate_location_list = 1

nnoremap <F5> :YcmForceCompileAndDiagnostics<CR>
nnoremap <F9> :YcmCompleter FixIt<CR>
nnoremap <leader>jd :YcmCompleter GoTo<CR>

