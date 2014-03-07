mozjpeg
-------

* [GitHub: mozjpeg](https://github.com/mozilla/mozjpeg).
* [Introducing the ‘mozjpeg’ Project](https://blog.mozilla.org/research/2014/03/05/introducing-the-mozjpeg-project/).
* [Trellis quantization](http://en.wikipedia.org/wiki/Trellis_quantization).


### How to compile on OS X

First, install 'nasm' via macports.
Then, in a clean source dir, do this:

```
autoreconf -fiv
./configure --host x86_64-apple-darwin NASM=/opt/local/bin/nasm
make
```
