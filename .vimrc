set nocompatible
set autoindent
set ruler
set number
set spell
set tabstop=3
set shiftwidth=3
set softtabstop=3
set expandtab
filetype plugin indent on
syntax on
if has("autocmd")
   au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g`\"" | endif
endif
highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%81v.\+/
