    David Taubman: The sole reason
    for transcoding is to reduce the precinct size to the minimum value consistent
    with the existing code-blocks so that the data can be sent with the smallest
    possible increments, so as to minimize the transmission of redundant data to
    the client. The transcoded image has the same parameters as the original,
    whatever they were, with the exception that the precinct size has been reduced
    to the smallest acceptable value. Transcoding is lossless and is not
    computationally costly. \bf{If the image already has the smallest possible
    precincts for its code-blocks, the transcoding step does nothing and could be
    skipped in a different implementation of the server. However, it can be more
    efficient to access images on the server which have larger precincts.}}

    En el documento [Kakadu Survey Documentation](http://www.kakadusoftware.com/documents/Kakadu.pdf) aparece lo siguiente:

    The kdu_server transcode local code-streams on the fly, so as to make them
    more amenable to efficient and responsive interactive delivery over low
    bandwidth networks. }

    En el documento [The JPIk Protocol](http://www.kakadusoftware.com/documents/jpik.pdf) aparece lo siguiente:

    The JPIK protocol is based around the transfer of individual packets from
    small precincts, each containing quality increments from only a few code-
    blocks. While all JPEG2000 images must have relatively small code-blocks, not
    all JPEG2000 images need be partitioned into small precincts. The
    "kdu_server" deals with this by transcoding all images on the fly into
    representations involving small precincts. The Kakadu architecture permits
    such operations to be performed on-demand with very little computational load
    or memory.

    Ongoing data transfers within the JPIK protocol proceed at the level of
    JPEG2000 packets (a packet is a single quality layer of a single precinct),
    rather than code-blocks. To ensure fine spatial granularity for these
    transfers, the Kakadu server transcodes existing compressed data sources on
    the fly into compressed representations whose precincts are as small as
    possible. The minimum precinct dimensions are determined by the size of the
    code-blocks used to compress the image, since the server is unwilling to
    decode an re-code individual code-blocks. One advantage of this transcoding
    policy is that just about any valid JPEG2000 compressed image can be
    efficiently served up over a low bandwidth connection. Nevertheless,
    particular choices of compression parameters can substantially ease
    the burden on the server's memory and computational resources.
