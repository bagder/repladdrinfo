# repladdrinfo

This is an implementation of `getaddrinfo` and `freeaddrinfo` made to use
c-ares.

They should work as drop-in replacements, but because of implementation
details they might not work 100% identical in all corner cases.

A primary motivator for me to work on this is to make a curl build that uses
`getaddrinfo` still be able to use a custom DNS server for debug builds, and
we can have c-ares do that. Doing that with the "real" getaddrinfo is not
easy.
