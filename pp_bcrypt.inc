// -
// Include Guards
// -

#if defined _INC_pp_bcrypt
    #endinput
#endif
#define _INC_pp_bcrypt


// -
// External Packages
// -

#if !defined _PawnPlus_included
    #error You need PawnPlus. Get it from IS4Code/PawnPlus.
#endif

#if !defined bcrypt_included && !defined _samp_bcrypt_included
    #error You need a BCrypt plugin. Get it from either Sreyas-Sreelal/samp-bcrypt or lassir/bcrypt-samp.
#endif


// -
// Declarations
// -

#if !defined BCRYPT_COST
    #define BCRYPT_COST 12
#endif

static stock gs_processIndex;


// -
// API
// -

forward _pp@OnDummyBCryptHash(index);
public _pp@OnDummyBCryptHash(index) return 1;

forward _pp@OnBCryptHashHandler(CallbackHandler:id, Task:t, processIndex, index);
public _pp@OnBCryptHashHandler(CallbackHandler:id, Task:t, processIndex, index)
{
    if (processIndex == index) {
        pawn_unregister_callback(id);

        new hash[BCRYPT_HASH_LENGTH];
        bcrypt_get_hash(hash);

        task_set_result_str(t, hash);
    }
    return 1;
}

stock Task:BCrypt_AsyncHash(const input[], cost = BCRYPT_COST)
{
    new Task:t = task_new();
    pawn_register_callback(
        pawn_nameof(_pp@OnDummyBCryptHash),
        pawn_nameof(_pp@OnBCryptHashHandler),
        _,
        "eii",
        t,
        gs_processIndex
    );

    #if defined _samp_bcrypt_included
        bcrypt_hash(gs_processIndex, pawn_nameof(_pp@OnDummyBCryptHash), input, cost);
    #elseif defined bcrypt_included
        bcrypt_hash(input, cost, pawn_nameof(_pp@OnDummyBCryptHash), "i", gs_processIndex);
    #endif
    
    gs_processIndex++;
    if (gs_processIndex >= cellmax) {
        gs_processIndex = 0;
    }

    return t;
}

#if defined _samp_bcrypt_included
    forward _pp@OnDummyBCryptVerify(index, bool:isVerified);
    public _pp@OnDummyBCryptVerify(index, bool:isVerified) return 1;
#elseif defined bcrypt_included
    forward _pp@OnDummyBCryptVerify(index);
    public _pp@OnDummyBCryptVerify(index) return 1;
#endif

#if defined _samp_bcrypt_included
    forward _pp@OnBCryptVerifyHandler(CallbackHandler:id, Task:t, processIndex, index, bool:isVerified);
    public _pp@OnBCryptVerifyHandler(CallbackHandler:id, Task:t, processIndex, index, bool:isVerified)
#elseif defined bcrypt_included
    forward _pp@OnBCryptVerifyHandler(CallbackHandler:id, Task:t, processIndex, index);
    public _pp@OnBCryptVerifyHandler(CallbackHandler:id, Task:t, processIndex, index)
#endif
{
    if (processIndex == index) {
        pawn_unregister_callback(id);

        #if defined bcrypt_included
            new bool:isVerified = bcrypt_is_equal();
        #endif

        task_set_result(t, isVerified);
    }
    return 1;
}

stock Task:BCrypt_AsyncVerify(const input[], const hash[])
{
    new Task:t = task_new();
    pawn_register_callback(
        pawn_nameof(_pp@OnDummyBCryptVerify),
        pawn_nameof(_pp@OnBCryptVerifyHandler),
        _,
        "eii",
        t,
        gs_processIndex
    );

    #if defined _samp_bcrypt_included
        bcrypt_verify(gs_processIndex, pawn_nameof(_pp@OnDummyBCryptVerify), input, hash);
    #elseif defined bcrypt_included
        bcrypt_check(input, hash, pawn_nameof(_pp@OnDummyBCryptVerify), "i", gs_processIndex);
    #endif

    gs_processIndex++;
    if (gs_processIndex >= cellmax) {
        gs_processIndex = 0;
    }

    return t;
}

