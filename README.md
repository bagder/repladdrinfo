# repladdrinfo

This is an implementation of `getaddrinfo` and `freeaddrinfo` made to use
c-ares.

They should work as drop-in replacements, but because of implementation
details they might not work 100% identical in all corner cases.

A primary motivator for me to work on this is to enable curl build that uses
`getaddrinfo` to still be able to use our custom DNS server for debug builds,
and we can have c-ares do that.
