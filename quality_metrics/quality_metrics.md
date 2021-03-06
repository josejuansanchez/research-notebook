## Quality Comparison Algorithms

Four of the most respected algorithms. 

* **Y-SSIM**  
  Structural Similarity algorithm [1] applied to luma channel only.

* **RGB-SSIM**  
  Average of Structural Similarity algorithm [1] applied to R, G, and B channels.

* **IW-SSIM**  
  Information Content Weighted Structural Similarity algorithm [2] applied to luma channel only.

* **PSNR-HVS-M**  
  Peak Signal to Noise Ratio taking into account Contrast Sensitivity Function (CSF) and between-coefficient contrast masking of DCT basis functions [3].

All of these algorithms compare two images and return a number indicating the degree to which the second image is similar to the first. In all cases, no matter what the scale, higher numbers indicate a higher degree of similarity.

It's unclear which algorithm is best in terms of human visual perception.

An implementation of these algorithms can be found on [github](https://github.com/bdaehlie/web_image_formats).

In October of 2013, Mozilla Corporation published a study entitled ["Lossy Compressed Image Formats Study"](http://people.mozilla.org/~josh/lossy_compressed_image_study_october_2013/) where they tested the aforementioned algorithms.


### Image
* [Survey on an Image Quality Assessment Metric Based on Early Vision Features &raquo;](http://www.ijsce.org/attachments/File/v2i6/F1184112612.pdf)

### Video
* [Survey of Objective Video Quality Measurements &raquo;](ftp://ftp.cs.wpi.edu/pub/techreports/pdf/06-02.pdf)


### References

1. [The SSIM Index for Image Quality Assessment](http://www.cns.nyu.edu/~lcv/ssim/).  
  [Zhou Wang](http://www.ece.uwaterloo.ca/~z70wang/), [Alan C. Bovik](http://live.ece.utexas.edu/people/bovik/), [Hamid R. Sheikh](http://live.ece.utexas.edu/People/people_detail.php?id=92) and [Eero P. Simoncelli](http://www.cns.nyu.edu/~eero/).

2. [IW-SSIM: Information Content Weighted Structural Similarity Index for Image Quality Assessment](https://ece.uwaterloo.ca/~z70wang/research/iwssim/).  
  Zhou Wang and Qiang Li, "Information Content Weighting for Perceptual Image Quality Assessment," IEEE Transactions on Image Processing, vol. 20, no. 5, pp. 1185-1198, May 2011.

3. [Nikolay Ponomarenko homepage - PSNR-HVS-M download page](http://www.ponomarenko.info/psnrhvsm.htm).  
  Nikolay Ponomarenko, Flavia Silvestri, Karen Egiazarian, Marco Carli, Jaakko Astola, Vladimir Lukin, On between-coefficient contrast masking of DCT basis functions, CD-ROM Proceedings of the Third International Workshop on Video Processing and Quality Metrics for Consumer Electronics VPQM-07, Scottsdale, Arizona, USA, 25-26 January, 2007, 4 p.



