if !has('gui_running') || (!has('win32') && !has('win64'))
  finish
endif

let g:vimtweak_dll_path = expand('<sfile>:p:h:h') . has('win64') ? '/vimtweak64.dll' : '/vimtweak32.dll'



command! -nargs=1 VimTweakSetAlpha call libcallnr(g:vimtweak_dll_path, "SetAlpha", 0+<args>)
command! VimTweakEnableMaximize call libcallnr(g:vimtweak_dll_path, "EnableMaximize", 1)
command! VimTweakDisableMaximize call libcallnr(g:vimtweak_dll_path, "EnableMaximize", 0)
command! VimTweakEnableTopMost call libcallnr(g:vimtweak_dll_path, "EnableTopMost", 1)
command! VimTweakDisableTopMost call libcallnr(g:vimtweak_dll_path, "EnableTopMost", 0)
