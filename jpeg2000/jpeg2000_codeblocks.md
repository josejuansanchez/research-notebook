## JPEG2000 codeblocks
* [Implication of variable code block size in JPEG 2000 and its VLSI implementation](http://www.researchgate.net/publication/229019964_Implication_of_variable_code_block_size_in_JPEG_2000_and_its_VLSI_implementation/file/9c960516d07ce29dc2.pdf). 

In JPEG 2000 standard, all the code blocks within the same tile of a component need to have the same width and height 
according to the JPEG 2000 standard. The width and height information of a code block are specified in either the 
coding style default (COD) and/or coding style component (COC) marker segments. However, the constraint of fixed 
code block size is due to the fact that COD and/or COC marker segments in a JPEG 2000 compressed file only can carry 
one set of code block width and height information for an image or a tile or a component. We have studied the 
implication of using variable code block sizes at different DWT resolution levels instead of the fixed size code blocks 
prescribed by JPEG 2000 standard. The simulation results show that there is no significant impact on compression 
efficiency if one uses different code block sizes at different DWT levels compared to the fixed size code block size.

* [Default code-block dimensions in kdu_compress]()

#### What is the best code-block dimension?

There is no clear answer to the question of which block size is best.  64x64 gives the
maximum coding efficiency (minimum distortion for given coded size) almost always
with 32x32 some few percent less efficient.  64x64 usually also results in slightly
faster processing since there are slightly less processing overheads.  


#### Why is 64x64 the default code-block dimension in kdu_compress?

The main reason we have always left 64x64 as the default is that it reduces the risk that
others might blindly use 32x32 in benchmarking the compression efficiency of
JPEG2000.


#### If 32x32 is the best option, why kdu_compress does not use 32x32 as default block dimensions?

On the other hand, 32x32 blocks given finer granularity which leads to more efficient
service of small windows of interest via JPIP.  Also 32x32 blocks end up requiring
only half the processing memory during encoding or decoding.