## Kakadu JPEG2000 Discussion Group
* [Custom Java JPIP Server with Kakadu API](https://groups.yahoo.com/neo/groups/kakadu_jpeg2000/conversations/messages/6910)
* [JPIP Sessions and channels](https://groups.yahoo.com/neo/groups/kakadu_jpeg2000/conversations/messages/6078)

JPIP is a pre-emptive protocol:

```
The main reason why Kakadu prefers to see sockets associated
with individual sessions is that JPIP is a pre-emptive protocol.
This means that the arrival of a new request is usually supposed
to pre-empt an ongoing response to a previous request.  This
pre-emptive mechanism is difficult to implement reliably when
constantly passing the channel around to different handling
threads.  It would be possible to do it better if we could be
sure that all requests followed the HTTP-TCP transport, so that
response data did not get interleaved with response headers, but
the current implementation recognizes that most clients will use
pure HTTP.  In this event, the use of one socket for multiple
sessions should be strongly discouraged for reasons which
should make sense if you think about it for a while.
```
