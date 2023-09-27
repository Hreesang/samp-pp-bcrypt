#include <a_samp>

#define PP_SYNTAX_AWAIT
#define PP_SYNTAX_YIELD

#include <PawnPlus>
#include <sscanf2>
#include <my_cmd>
#include <test-boilerplate>

#include <samp_bcrypt>
#warning pp_bcrypt test is built using Syreas' bcrypt.

#include "pp_bcrypt"

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

main() {}

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