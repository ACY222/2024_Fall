set nocompatible 	" not vi compatible

syntax on  			" turn on syntax highlighting
" set showmatch 		" show matching braces when text indicator is over them

set shortmess+=I 	" Disable the default Vim startup message

set number   		" number lines		 
set relativenumber 	" relative number lines
set laststatus=2  	" always show the status line at the buttom
set backspace=indent,eol,start 	" allow backspacing over everything
set hidden 			" enable to hidden buffers
set ignorecase 		" smart case-sensitive search
set smartcase 		
set incsearch 		" searching as you type
set hls 			" highlight search
set showcmd 		" display inputting commands
filetype plugin indent on 		" enable file type detection
set autoindent 					" stay the same with last line after typing enter
set cindent			" use c indent 
set sm				" highlight matched braces shortly
set matchtime=25	" highlight time(ms)

set makeprg=g++\ %\ -o\ %<\.exe
" use F6 to compile, F5 to execute
map <F6> :w<CR>:make<CR>	
map <F5> :!./%<.exe<CR>		

set tabstop=4 		" the size of tab
set softtabstop=4
set shiftwidth=4

set textwidth=80    " the width of each line
set wrap            " break lines automatically
set linebreak       " break only when encountering with specific character
set scrolloff=15
match ErrorMsg '\%>80v.\+'	" highlight the characters above 80

set nobackup                " don't create backup file
set noswapfile              " don't create swap file
set undofile                " create undo file
set undodir=~/.vim/.undo//
set history=100             " record 100 operations

set autochdir               " change directory when open a new file

set autoread                " when editing files are changed in other place

set wildmenu
set wildmode=longest,list,full
" Unbind some useless/annoying default key bindings.
nmap Q <Nop>
"
" Disable audible bell
set noerrorbells visualbell t_vb=

" Enable mouse support. You should avoid relying on this too much, but it can
" sometimes be convenient.
set mouse+=a

" open new split panes to right and bottom, which feels more natural
set splitbelow
set splitright

nnoremap <Left>  :echoe "Use h"<CR>
nnoremap <Right> :echoe "Use l"<CR>
nnoremap <Up>    :echoe "Use k"<CR>
nnoremap <Down>  :echoe "Use j"<CR>

inoremap <Left>  <ESC>:echoe "Use h"<CR>
inoremap <Right> <ESC>:echoe "Use l"<CR>
inoremap <Up>    <ESC>:echoe "Use k"<CR>
inoremap <Down>  <ESC>:echoe "Use j"<CR>


call plug#begin('~/.vim/plugged')
" file construction
Plug 'majutsushi/tagbar'	
" directory overview
Plug 'scrooloose/nerdtree'
Plug 'jiangmiao/auto-pairs'
" vim themes
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'rakr/vim-one'
call plug#end()

" tagbar settings
let g:tagbar_ctags_bin  = 'ctags'
let g:tagbar_width		= 30
let g:tagbar_autofocus  = 1
let g:tagbar_left		= 1
let g:tagbar_sort		= 0
" map t :TagbarToggle<CR>

" Nerdtree Settings
" Press F3 to show or hide the nerd tree
map <F3> :NERDTreeMirror<CR>
map <F3> :NERDTreeToggle<CR>
let NERDTreeShowHidden=0

" airline and vim-one settings
"--- vim-airline-themes' ---                     
let g:airline#extensions#tabline#enabled=1
let g:airline_theme='one'
colorscheme one
set background=dark " for the dark version
"
"Credit joshdick
"Use 24-bit (true-color) mode in Vim/Neovim when outside tmux.
"If you're using tmux version 2.2 or later, you can remove the outermost $TMUX check and use tmux's 24-bit color support
"(see < http://sunaku.github.io/tmux-24bit-color.html#usage > for more information.)
if (empty($TMUX))
  if (has("nvim"))
    "For Neovim 0.1.3 and 0.1.4 < https://github.com/neovim/neovim/pull/2198 >
    let $NVIM_TUI_ENABLE_TRUE_COLOR=1
  endif
  "For Neovim > 0.1.5 and Vim > patch 7.4.1799 < https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162 >
  "Based on Vim patch 7.4.1770 (`guicolors` option) < https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd >
  " < https://github.com/neovim/neovim/wiki/Following-HEAD#20160511 >
  if (has("termguicolors"))
    set termguicolors
  endif
endif


function! s:check_back_space() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

inoremap <expr><S-TAB> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

