 #include <cstddef>
#include <cstdint>
#include <memory>
#include <set>
#include <vector>
#include <string>
#include <cryptofuzz/options.h>
#include <fuzzing/datasource/id.hpp>
#include "repository_tbl.h"
#include "driver.h"
#include "numbers.h"
#include "mutatorpool.h"

#if defined(CRYPTOFUZZ_LIBTOMMATH) && defined(CRYPTOFUZZ_NSS)
#error "libtommath and NSS cannot be used together due to symbol collisions"
#endif

#if defined(CRYPTOFUZZ_TREZOR_FIRMWARE) && defined(CRYPTOFUZZ_RELIC)
#error "trezor-firmware and relic cannot be used together due to symbol collisions"
#endif

#if !defined(CRYPTOFUZZ_NO_OPENSSL)
  #include <modules/openssl/module.h>
  #ifdef SHA1
    #undef SHA1
  #endif
  #ifdef SHA224
    #undef SHA224
  #endif
  #ifdef SHA256
    #undef SHA256
  #endif
  #ifdef SHA384
    #undef SHA384
  #endif
  #ifdef SHA512
    #undef SHA512
  #endif
#endif

#if defined(CRYPTOFUZZ_BITCOIN)
  #include <modules/bitcoin/module.h>
#endif

#if defined(CRYPTOFUZZ_REFERENCE)
  #include <modules/reference/module.h>
#endif

#if defined(CRYPTOFUZZ_CPPCRYPTO)
  #include <modules/cppcrypto/module.h>
#endif

#if defined(CRYPTOFUZZ_MBEDTLS)
  #include <modules/mbedtls/module.h>
#endif

#if defined(CRYPTOFUZZ_BOOST)
  #include <modules/boost/module.h>
#endif

#if defined(CRYPTOFUZZ_MONERO)
  #include <modules/monero/module.h>
#endif

#if defined(CRYPTOFUZZ_VERACRYPT)
  #include <modules/veracrypt/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBSODIUM)
  #include <modules/libsodium/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBTOMCRYPT)
  #include <modules/libtomcrypt/module.h>
#endif

#if defined(CRYPTOFUZZ_CRYPTOPP)
  #include <modules/cryptopp/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBGCRYPT)
  #include <modules/libgcrypt/module.h>
#endif

#if defined(CRYPTOFUZZ_EVERCRYPT)
  #include <modules/evercrypt/module.h>
#endif

#if defined(CRYPTOFUZZ_GOLANG)
  #include <modules/golang/module.h>
#endif

#if defined(CRYPTOFUZZ_RING)
  #include <modules/ring/module.h>
#endif

#if defined(CRYPTOFUZZ_NSS)
  #include <modules/nss/module.h>
#endif

#if defined(CRYPTOFUZZ_BOTAN)
  #include <modules/botan/module.h>
#endif

#if defined(CRYPTOFUZZ_NETTLE)
  #include <modules/nettle/module.h>
#endif

#if defined(CRYPTOFUZZ_WOLFCRYPT)
  #include <modules/wolfcrypt/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBGMP)
  #include <modules/libgmp/module.h>
#endif

#if defined(CRYPTOFUZZ_BN_JS)
  #include <modules/bn.js/module.h>
#endif

#if defined(CRYPTOFUZZ_CRYPTO_JS)
  #include <modules/crypto-js/module.h>
#endif

#if defined(CRYPTOFUZZ_BIGNUMBER_JS)
  #include <modules/bignumber.js/module.h>
#endif

#if defined(CRYPTOFUZZ_MPDECIMAL)
  #include <modules/mpdecimal/module.h>
#endif

#if defined(CRYPTOFUZZ_LINUX)
  #include <modules/linux/module.h>
#endif

#if defined(CRYPTOFUZZ_SYMCRYPT)
  #include <modules/symcrypt/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBTOMMATH)
  #include <modules/libtommath/module.h>
#endif

#if defined(CRYPTOFUZZ_SJCL)
  #include <modules/sjcl/module.h>
#endif

#if defined(CRYPTOFUZZ_WOLFCRYPT_OPENSSL)
  #include <modules/wolfcrypt-openssl/module.h>
#endif

#if defined(CRYPTOFUZZ_MONOCYPHER)
  #include <modules/monocypher/module.h>
#endif

#if defined(CRYPTOFUZZ_SECP256K1)
  #include <modules/secp256k1/module.h>
#endif

#if defined(CRYPTOFUZZ_RUST_LIBSECP256K1)
  #include <modules/rust-libsecp256k1/module.h>
#endif

#if defined(CRYPTOFUZZ_TREZOR_FIRMWARE)
  #include <modules/trezor/module.h>
#endif

#if defined(CRYPTOFUZZ_ELLIPTIC)
  #include <modules/elliptic/module.h>
#endif

#if defined(CRYPTOFUZZ_DECRED)
  #include <modules/decred/module.h>
#endif

#if defined(CRYPTOFUZZ_BEARSSL)
  #include <modules/bearssl/module.h>
#endif

#if defined(CRYPTOFUZZ_MICRO_ECC)
  #include <modules/micro-ecc/module.h>
#endif

#if defined(CRYPTOFUZZ_CIFRA)
  #include <modules/cifra/module.h>
#endif

#if defined(CRYPTOFUZZ_RELIC)
  #include <modules/relic/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBECC)
  #include <modules/libecc/module.h>
#endif

#if defined(CRYPTOFUZZ_CHIA_BLS)
  #include <modules/chia_bls/module.h>
#endif

#if defined(CRYPTOFUZZ_K256)
  #include <modules/k256/module.h>
#endif

#if defined(CRYPTOFUZZ_SCHNORRKEL)
  #include <modules/schnorrkel/module.h>
#endif

#if defined(CRYPTOFUZZ_NOBLE_SECP256K1)
  #include <modules/noble-secp256k1/module.h>
#endif

#if defined(CRYPTOFUZZ_NOBLE_CURVES)
  #include <modules/noble-curves/module.h>
#endif

#if defined(CRYPTOFUZZ_BLST)
  #include <modules/blst/module.h>
#endif

#if defined(CRYPTOFUZZ_MCL)
  #include <modules/mcl/module.h>
#endif

#if defined(CRYPTOFUZZ_PY_ECC)
  #include <modules/py_ecc/module.h>
#endif

#if defined(CRYPTOFUZZ_KILIC_BLS12_381)
  #include <modules/kilic-bls12-381/module.h>
#endif

#if defined(CRYPTOFUZZ_NOBLE_ED25519)
  #include <modules/noble-ed25519/module.h>
#endif

#if defined(CRYPTOFUZZ_NOBLE_BLS12_381)
  #include <modules/noble-bls12-381/module.h>
#endif

#if defined(CRYPTOFUZZ_SCHNORR_FUN)
  #include <modules/schnorr_fun/module.h>
#endif

#if defined(CRYPTOFUZZ_QUICKJS)
  #include <modules/quickjs/module.h>
#endif

#if defined(CRYPTOFUZZ_UINT128_T)
  #include <modules/uint128_t/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBFF)
  #include <modules/libff/module.h>
#endif

#if defined(CRYPTOFUZZ_GNARK_BN254)
  #include <modules/gnark-bn254/module.h>
#endif

#if defined(CRYPTOFUZZ_GOOGLE_BN256)
  #include <modules/google-bn256/module.h>
#endif

#if defined(CRYPTOFUZZ_CLOUDFLARE_BN256)
  #include <modules/cloudflare-bn256/module.h>
#endif

#if defined(CRYPTOFUZZ_NOBLE_HASHES)
  #include <modules/noble-hashes/module.h>
#endif

#if defined(CRYPTOFUZZ_SKALE_SOLIDITY)
  #include <modules/skalesolidity/module.h>
#endif

#if defined(CRYPTOFUZZ_GOOGLE_INTEGERS)
  #include <modules/google-integers/module.h>
#endif

#if defined(CRYPTOFUZZ_NIMCRYPTO)
  #include <modules/nimcrypto/module.h>
#endif

#if defined(CRYPTOFUZZ_RUSTCRYPTO)
  #include <modules/rustcrypto/module.h>
#endif

#if defined(CRYPTOFUZZ_NUM_BIGINT)
  #include <modules/num-bigint/module.h>
#endif

#if defined(CRYPTOFUZZ_INTX)
  #include <modules/intx/module.h>
#endif

#if defined(CRYPTOFUZZ_DECRED_UINT256)
  #include <modules/decred-uint256/module.h>
#endif

#if defined(CRYPTOFUZZ_LIBDIVIDE)
  #include <modules/libdivide/module.h>
#endif

#if defined(CRYPTOFUZZ_RUST_UINT)
  #include <modules/rust-uint/module.h>
#endif

#if defined(CRYPTOFUZZ_BC)
  #include <modules/bc/module.h>
#endif

#if defined(CRYPTOFUZZ_JAVA)
  #include <modules/java/module.h>
#endif

#if defined(CRYPTOFUZZ_SOLIDITY_MATH)
  #include <modules/soliditymath/module.h>
#endif

#if defined(CRYPTOFUZZ_V8)
  #include <modules/v8/module.h>
#endif

#if defined(CRYPTOFUZZ_CIRCL)
  #include <modules/circl/module.h>
#endif

#if defined(CRYPTOFUZZ_SPL_MATH)
  #include <modules/spl_math/module.h>
#endif

#if defined(CRYPTOFUZZ_ZIG)
  #include <modules/zig/module.h>
#endif

#if defined(CRYPTOFUZZ_PRYSMATICLABS_HASHTREE)
  #include <modules/prysmaticlabs-hashtree/module.h>
#endif

#if defined(CRYPTOFUZZ_STARKWARE)
  #include <modules/starkware/module.h>
#endif

#if defined(CRYPTOFUZZ_PORNIN_BINGCD)
  #include <modules/pornin-bingcd/module.h>
#endif

#if defined(CRYPTOFUZZ_STINT)
  #include <modules/stint/module.h>
#endif

#if defined(CRYPTOFUZZ_KRYPTOLOGY)
  #include <modules/kryptology/module.h>
#endif

#if defined(CRYPTOFUZZ_NIM_BIGINTS)
  #include <modules/nim-bigints/module.h>
#endif

#if defined(CRYPTOFUZZ_HOLIMAN_UINT256)
  #include <modules/holiman-uint256/module.h>
#endif

#if defined(CRYPTOFUZZ_CPU)
  #include <modules/cpu/module.h>
#endif

#if defined(CRYPTOFUZZ_GETH)
  #include <modules/geth/module.h>
#endif

#if defined(CRYPTOFUZZ_JSBN)
  #include <modules/jsbn/module.h>
#endif

#if defined(CRYPTOFUZZ_WIDE_INTEGER)
  #include <modules/wide-integer/module.h>
#endif

#if defined(CRYPTOFUZZ_TINY_KECCAK)
  #include <modules/tiny-keccak/module.h>
#endif

#if defined(CRYPTOFUZZ_ARKWORKS_ALGEBRA)
  #include <modules/arkworks-algebra/module.h>
#endif

#if defined(CRYPTOFUZZ_FF)
  #include <modules/ff/module.h>
#endif

#if defined(CRYPTOFUZZ_ALEO)
  #include <modules/aleo/module.h>
#endif

#if defined(CRYPTOFUZZ_SHAMATAR)
  #include <modules/shamatar/module.h>
#endif

#if defined(CRYPTOFUZZ_MICROSOFT_CALCULATOR)
  #include <modules/microsoft-calculator/module.h>
#endif

#if defined(CRYPTOFUZZ_POLYGON_ZKEVM_PROVER)
  #include <modules/polygon-zkevm-prover/module.h>
#endif

#if defined(CRYPTOFUZZ_GOLDILOCKS)
  #include <modules/goldilocks/module.h>
#endif

#if defined(CRYPTOFUZZ_D)
  #include <modules/d/module.h>
#endif

#if defined(CRYPTOFUZZ_PAIRING_CE)
  #include <modules/pairing_ce/module.h>
#endif

#if defined(CRYPTOFUZZ_PASTA_CURVES)
  #include <modules/pasta_curves/module.h>
#endif

#if defined(CRYPTOFUZZ_BOUNCYCASTLE)
  #include <modules/bouncycastle/module.h>
#endif

#if defined(CRYPTOFUZZ_FAHEEL_BIGINT)
  #include <modules/faheel-bigint/module.h>
#endif

#if defined(CRYPTOFUZZ_SUBSTRATE_BN)
  #include <modules/substrate-bn/module.h>
#endif

#if defined(CRYPTOFUZZ_AURORA_ENGINE_MODEXP)
  #include <modules/aurora-engine-modexp/module.h>
#endif

#if defined(CRYPTOFUZZ_V8_EMBEDDED)
  #include <modules/v8-embedded/module.h>
#endif

#if defined(CRYPTOFUZZ_CONSTANTINE)
  #include <modules/constantine/module.h>
#endif

std::shared_ptr<cryptofuzz::Driver> driver = nullptr;

const cryptofuzz::Options* cryptofuzz_options = nullptr;

static void setOptions(int argc, char** argv) {
    std::vector<std::string> extraArguments;

    const std::string cmdline(
#include "extra_options.h"
    );
    boost::split(extraArguments, cmdline, boost::is_any_of(" "));

    const cryptofuzz::Options options(argc, argv, extraArguments);

    driver = std::make_shared<cryptofuzz::Driver>(options);
    cryptofuzz_options = driver->GetOptionsPtr();
}

static void addNumbers(void) {
    std::set<std::string> curveNumbers;

    for (size_t i = 0; i < (sizeof(ECC_CurveLUT) / sizeof(ECC_CurveLUT[0])); i++) {
        if ( ECC_CurveLUT[i].prime ) curveNumbers.insert(*ECC_CurveLUT[i].prime);
        if ( ECC_CurveLUT[i].a ) curveNumbers.insert(*ECC_CurveLUT[i].a);
        if ( ECC_CurveLUT[i].b ) curveNumbers.insert(*ECC_CurveLUT[i].b);
        if ( ECC_CurveLUT[i].x ) curveNumbers.insert(*ECC_CurveLUT[i].x);
        if ( ECC_CurveLUT[i].y ) curveNumbers.insert(*ECC_CurveLUT[i].y);
        if ( ECC_CurveLUT[i].order_min_1 ) curveNumbers.insert(*ECC_CurveLUT[i].order_min_1);
        if ( ECC_CurveLUT[i].order ) curveNumbers.insert(*ECC_CurveLUT[i].order);
        if ( ECC_CurveLUT[i].cube_root_of_unity ) curveNumbers.insert(*ECC_CurveLUT[i].cube_root_of_unity);
    }

    for (const auto& s : curveNumbers) {
        cryptofuzz::numbers.push_back(s);
    }
}

static void addDHParameters(void) {
#if 0
    Pool_DSA_PQG.Set(
            {.p = "1",
            .q = "2",
            .g = "3"});
#endif
    Pool_DSA_PQG.Set(
            {.p = "150231251465501053065289730830479539031267100291054217656119618775188714462742252299995155757488154161365770046117427638242442140226792437461696203428042747814919633220489019161055283800701437723694062141157721435870605677289344980419875189236552985653350450140879697446183075783979747578514684880689288047799",
            .q = "1294481460557625951125096174768278956450379329019",
            .g = "123176323926370145306905001771640082099315258804911565991781248774641279332286091530406470110108628420952674474326303976152638457646984169382680970876359186878615754700522570368203249170942652654272930135088255007459054551060675803532305465059607033300717516344741377807058295415130769662943475898885953255340"});
    Pool_DSA_PQG.Set(
            {.p = "106509719202367738942907301715621764539176496646576730633405674043673327856034496732123285709035111374434625191651676418221653833534278937120432644397709949603105722781668399360019469472968954460534436252768055503483520304713097271043340825087067201677304620852378413654560436979990703753937487367926506348269",
            .q = "1118288236462792761843833248187413414208173350127",
            .g = "72435671226965183258018862642795284302154495588562538482929411018310293659579761499337602974793436767341017333127333555852102593771624671345177391442816067820254123593555250556535136260966363205479876316378634773122750273117965996152020834617159357433557924693138598393331986343698108999770366446752278926383"});
    Pool_DSA_PQG.Set(
            {.p = "138004309818347094291132867053619499223956524961247192036762792751710974956820647583519309378416103935248269857717426029960774699149947213109440086871278734506662709841063082677937025903550210186986005638869595390211739861476658649538254442080037424128091536935132784096865076724077340725421734957662003955733",
            .q = "1182250927352833565111471235946595886633807053753",
            .g = "50981117407618898907676270875500924244946234557748656321451486290931484477672699528123700670310821778249759666738775273571334004072876741139654244496478237072456811279416350268794526824840182161332334555442145925212778889513472053306551473115435240639581353186943034554008455203164569371804149410594860147535"});
    Pool_DSA_PQG.Set(
            {.p = "109946688229802800321045008502525855019018343635199811459637834412277718704275426696546931048200193867073853699694661301100987130977969037055869145785556128499893546459160327648034486774397840709962126663410720743324891206859744100608443126416778329748285936795477961285242132107013514469104031276590639145529",
            .q = "1097017798574652758688027153013343959247758036379",
            .g = "90853802403425362444834708006843703424758064889418913931212173026894777531419682953836039048180446572898657640543499059154888760571238291120015914403667178235563530884249409802138323217540531374295893371508604222324367014390024227163670654837119886355437741902577247163114711575830541075372536310906966739501"});
    Pool_DSA_PQG.Set(
            {.p = "124209509072024958275166637845461843473168024436234587545357618943183152164739154230608140142817940602971118647920318657635219309456829210930848667888289103140463427808821865872498412912378809701133733363511757593195923487399372820407763609428150569455525396831100333605708326427075191467209382555105711963299",
            .q = "1156817815916336365281547542987775955291851935871",
            .g = "43439798865518148079170184647168882910799658250950112656992473391369195267567114318131636772383729066568167011041675228166469202932063704475384188208092171311430491566372323746821632363680716780126497417783638448391870877258448510742322506027897962466869528155419123258766935809190262469523993336422700725318"});
    Pool_DSA_PQG.Set(
            {.p = "126331233628980840165184565942245385096513091144740711497864308287507943295406615416955002027235910171772121228535928494648768972393171048104219309808822924104348781037865255204637472392028547550836119757782109037132097469719594436136398329796267499263632942017207769135383159876183961765810415630873971115233",
            .q = "1203327632657956941015344776779451299508739578129",
            .g = "974526682858198650556593114150439136784016348485121330773151514044162030002440826516399445158900027525522996408279698970975943327455789546181341418095168135883533744340670987494788840118392