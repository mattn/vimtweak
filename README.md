# VimTweak

## What is this

This is a tweaking dll for GVim.

## Install

copy vimtweak32.dll or vimtweak64.dll into same directory with gvim.exe

## Usage

### Alpha Window

#### For example, 200/255 alpha

```
:call libcallnr("vimtweak.dll", "SetAlpha", 200)
```

#### reset alpha

```
:call libcallnr("vimtweak.dll", "SetAlpha", 255)
```

### Maximized Window

#### Enable

```
:call libcallnr("vimtweak.dll", "EnableMaximize", 1)
```

#### Disable

```
:call libcallnr("vimtweak.dll", "EnableMaximize", 0)
```

### TopMost Window

#### Enable

```
:call libcallnr("vimtweak.dll", "EnableTopMost", 1)
```

#### Disable

```
:call libcallnr("vimtweak.dll", "EnableTopMost", 0)
```

## License

MIT

## Author

Yasuhiro Matsumoto (a.k.a mattn)
