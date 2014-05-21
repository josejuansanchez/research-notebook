HTTP Adaptive Streaming
=======================

### Introduction

> [Adaptive bitrate streaming](http://en.wikipedia.org/wiki/Adaptive_bitrate_streaming) from Wikipedia.

Adaptive bitrate streaming is a technique used in streaming multimedia over computer networks. While in the past most video streaming technologies utilized streaming protocols such as RTP with RTSP, today's adaptive streaming technologies are almost exclusively based on HTTP and designed to work efficiently over large distributed HTTP networks such as the Internet.

It works by detecting a *user's bandwidth* and *CPU capacity* in real time and adjusting the quality of a video stream accordingly. It requires the use of an encoder which can encode a single source video at multiple bit rates. The player client switches between streaming the different encodings depending on available resources.

![Adaptive streaming overview bit rates](http://upload.wikimedia.org/wikipedia/commons/thumb/9/99/Adaptive_streaming_overview_bit_rates_2011_07_28.png/800px-Adaptive_streaming_overview_bit_rates_2011_07_28.png)

Figure 1. This image is licensed under the CC [Attribution-Share Alike 3.0 Unported](http://creativecommons.org/licenses/by-sa/3.0/deed.en) license.


### Implementations
  * MPEG-DASH
  * YouTube Sliced Bread 
    * [Adaptive Streaming for You and YouTube. Google I/O 2013](https://developers.google.com/events/io/sessions/328181796)
  * Adobe Dynamic Streaming for Flash
  * Apple HTTP Adaptive Streaming for iOS
  * Microsoft Smooth Streaming
  * QuavStreams Adaptive Streaming over HTTP
  * upLynk

### MPEG-DASH

MPEG-DASH is the only adaptive bit-rate HTTP-based streaming solution that is an international standard.
The scope of the MPEG-DASH standard was limited to the Media Presentation Description (MPD) format of the manifest files as well as the segmentation standards for the server.

With the increase of Internet bandwidth and the tremendous growth of the World Wide Web, the value of delivering audio or video data in small packets has diminished. Multimedia content can now be delivered efficiently in larger segments using HTTP.

* [MPEG-DASH: The Standard for Multimedia Streaming Over Internet](http://mpeg.chiariglione.org/standards/mpeg-dash)
* [MPEG-DASH: Enabling Formats for Video Streaming over the Open Internet](https://tech.ebu.ch/docs/events/webinar043-mpeg-dash/presentations/ebu_mpeg-dash_webinar043.pdf)
* [MPEG-DASH: Tutorials](http://multimediacommunication.blogspot.co.at/2013/09/mpeg-dash-tutorials.html)
 

### DASH-AVC/264

In order to help speed adoption of MPEG-DASH, the DASH Industry Forum proposed a reduced specification, which was limited to a single Codec (AVC/h.264) and narrowed the options available within the MPD. This specification is known as DASH-264.5 As part of the DASH Industry Forum, Digital Primates was charged with building the DASH-264 reference client.

* [DASH Industry Forum](http://dashif.org)
* [Institute of Information Technology, Multimedia Communication (MMC) Group ](http://www-itec.aau.at/dash)
* [Bitmovin](http://www.bitmovin.net)
* [dash.js](https://github.com/Dash-Industry-Forum/dash.js). A reference client implementation for the playback of MPEG DASH via Javascript and compliant browsers.

### Papers and Presentations in Conferences
* [HTTP Adaptive Streaming: Principles, Ongoing Research and Standards](http://www.employees.org/~acbegen/files/HAS_Tutorial_ICME_2013_Begen_Stockhammer.pdf). ICME 2013. Ali C. Begen and  Thomas Stockhammer.
* [Caching in HTTP Adaptive Streaming: Friend or Foe?](http://www.employees.org/~acbegen/files/ACM_NOSSDAV14_abegen.pdf).
* [An Evaluation of Dynamic Adaptive Streaming over HTTP in Vehicular Environments](http://www-itec.uni-klu.ac.at/bib/files/p37-mueller.pdf). C. Müller, S. Lederer and C. Timmerer, In Proceedings of the ACM Multimedia Systems Conference 2012 and the 4th ACM Workshop on Mobile Video, Chapel Hill, North Carolina, February 24, 2012.

### Resources
* [Building an Online Video Player with DASH-264](http://flippinawesome.org/2013/11/18/building-an-online-video-player-with-dash-264/#)

### Resources in Spanish
* [DASH: Un estándar MPEG para streaming sobre HTTP](http://upcommons.upc.edu/pfc/bitstream/2099.1/16894/1/84799.pdf)
* [Avances y tendencias en la distribución de contenidos multimedia](http://www.scc.uned.es/jornadasmaster/pdf/Charla1.pdf)

### Glossary
* [OTT (Over the top)](http://en.wikipedia.org/wiki/Over-the-top_content).
* MPD. Media Presentation Description.

### People
* [Christian Timmerer](https://plus.google.com/+ChristianTimmerer/posts)