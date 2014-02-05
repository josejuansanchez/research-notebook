## Linux Tricks

* How to redirect stdout and stderr output messages to a file?

```
$ command > file.txt 2>&1
```

* PPM to YUV

```
$ cat images/*.ppm | ppmtoy4m > video.yuv
```

* YUV to PPM

```
$ y4mtoppm < video_input.y4m | pnmsplit - "%d.ppm"
```
