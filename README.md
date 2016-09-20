# VimTweak

## What is this

This is a tweaking dll for GVim.

## Install

copy vimtweak32.dll or vimtweak64.dll into same directory with gvim.exe

## Usage

### Alpha Window

#### For example, 200/255 alpha

```
:call libcallnr("vimtweak64.dll", "SetAlpha", 200)
```

#### reset alpha

```
:call libcallnr("vimtweak64.dll", "SetAlpha", 255)
```

### Maximized Window

#### Enable

```
:call libcallnr("vimtweak64.dll", "EnableMaximize", 1)
```

#### Disable

```
:call libcallnr("vimtweak64.dll", "EnableMaximize", 0)
```

### TopMost Window

#### Enable

```
:call libcallnr("vimtweak64.dll", "EnableTopMost", 1)
```

#### Disable

```
:call libcallnr("vimtweak64.dll", "EnableTopMost", 0)
```

## License

MIT

## Author

Yasuhiro Matsumoto (a.k.a mattn)
