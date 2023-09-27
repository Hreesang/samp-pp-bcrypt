# samp-pp-bcrypt

[![sampctl](https://img.shields.io/badge/sampctl-samp--pp--bcrypt-2f2f2f.svg?style=for-the-badge)](https://github.com/Hreesang/samp-pp-bcrypt)

This library expands the usage of BCrypt plugins in SA:MP or open.mp for `PawnPlus` async-await features. You're free to use either [Sryeas-Sreelal/samp-bcrypt](https://github.com/Sreyas-Sreelal/samp-bcrypt) or [lassir/bcrypt-samp](https://github.com/lassir/bcrypt-samp) as both are supported and the usage is the same, so you don't need to change functions or arguments when switching between plugins.

## Installation

Simply install to your project:

```bash
sampctl install Hreesang/samp-pp-bcrypt
```

Include in your code and begin using the library:

```c
#include <pp_bcrypt>
```

This library doesn't automatically install the supported BCrypt plugins, so you need to install them manually. You only need to choose one of them:

- [Sryeas-Sreelal/samp-bcrypt](https://github.com/Sreyas-Sreelal/samp-bcrypt)
- [lassir/bcrypt-samp](https://github.com/lassir/bcrypt-samp)

## Usage

```c
CMD:hash(playerid, const params[])
{
    if (isnull(params)) {
        return SendClientMessage(playerid, -1, "Usage: /hash [text]");
    }

    new hash[BCRYPT_HASH_LENGTH];
    yield 1;
    await_arr(hash) BCrypt_AsyncHash(params);

    new string[144];
    SendClientMessage(playerid, -1, "Command: /hash [text]");

    format(string, sizeof string, "Text: %s", params);
    SendClientMessage(playerid, -1, string);

    format(string, sizeof string, "Hash: %s", hash);
    SendClientMessage(playerid, -1, string);
    return 1;
}

CMD:verify(playerid, const params[])
{
    new hash[BCRYPT_HASH_LENGTH];
    new text[128];

    if (sscanf(params, "s[*]s[128]", sizeof hash, hash, text)) {
        return SendClientMessage(playerid, -1, "/verify [hash] [text]");
    }

    yield 1;
    new bool:isVerified = bool:await BCrypt_AsyncVerify(text, hash);

    new string[144];
    SendClientMessage(playerid, -1, "Command: /verify [hash] [text]");

    format(string, sizeof string, "Text: %s", text);
    SendClientMessage(playerid, -1, string);

    format(string, sizeof string, "Hash: %s", hash);
    SendClientMessage(playerid, -1, string);

    format(string, sizeof string, "Is Verified: %s", isVerified ? "Yes" : "No");
    SendClientMessage(playerid, -1, string);

    return 1;
}
```

## Functions

#### BCrypt_AsyncHash

> - **Parameters:**
> - - `const input[]`: input that needs to be hashed
> - - `cost = BCRYPT_COST`: bcrypt cost, default to `BCRYPT_COST` that is `12`.
> - **Returns:**
> - - `PawnPlus` task whose result is an array sized `BCRYPT_HASH_LENGTH`
> - **Remarks:**
> - - Returns the task that needs to be awaited

#### BCrypt_AsyncVerify

> - **Parameters:**
> - - `const input[]`: plain text
> - - `const hash[]`: hash that will be testified to `input`.
> - **Returns:**
> - - `PawnPlus` task whose result is a `true` boolean if verified or `false` if not
> - **Remarks:**
> - - Returns the verification result

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl run
```

## Credits

- [Sryeas-Sreelal](https://github.com/Sreyas-Sreelal) and [lassir](https://github.com/lassir) for the BCrypt plugins
- [IS4Code](https://github.com/IS4Code) for the PawnPlus
