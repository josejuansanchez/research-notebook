## Tricks

* ImageMagick: Append many images into one

If you want to append images horizontally, use this command
````
convert image1.jpg image2.jpg image3.jpg +append result.jpg
```` 

If you want to append them vertically, change the + to a -
````
convert image1.jpg image2.jpg image3.jpg -append result.jpg
````