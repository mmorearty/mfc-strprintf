# Printf directly to an MFC CString

This is a function which makes it easy to elegantly create a temporary `char*`
or `CString` and pass it as an argument, without having to explicitly create a
temporary variable.

A common problem: You need to format a string and then pass it to some
function, but it seems like a silly nuisance to have to explicitly create a
temporary buffer to hold the string, format into that buffer, and then call the
function. For example, you see code all the time that looks like this:

```c++
    if (/*some condition*/)
    {
        CString str;
        str.Format( "Important info: %d %s", n, s );
        SomeFunction(str);
    }
```

It would be so much cleaner to be able to write your code something like this:

```c++
    if (/*some condition*/)
        SomeFunction("Important info: %d %s", n, s);
```

However, that would require having a varargs constructor for `SomeFunction` --
and for every other similar function which takes a string as input.

But this function, `StrPrintf`, allows you to write the above example like
this, which is almost as good:

```c++
    if (/*some condition*/)
        SomeFunction( StrPrintf("Important info: %d %s", n, sz) );
```

This creates a temporary object on the stack of type `CString`; formats the
specified string into it; passes either a `CString` or a `(const char*)` to the
function; and then deletes the temporary object automatically.

[Whether a `CString` or a `(const char*)` gets passed depends on the prototype
of SomeFunction. `CString` supports an implicit cast to `(const char*)` -- or
to be more precise, to `(LPCTSTR)`. So the above line of code will implicitly
cast the `CString` to a `(const char*)` if necessary.]

Here's another example: This code...

```c++
    if (FAILED(hr))
    {
        CString s;
        s.Format("Error %X", hr);
        AfxMessageBox(s);
    }
```

...becomes this:

```c++
    if (FAILED(hr))
        AfxMessageBox( StrPrintf("Error %X", hr) );
```
