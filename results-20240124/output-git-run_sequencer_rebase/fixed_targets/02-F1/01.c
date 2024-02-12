#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "sequencer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct rebase_options opts;
  memset(&opts, 0, sizeof(opts));
  opts.force = stream.ConsumeBool();
  opts.quiet = stream.ConsumeBool();
  opts.verbose = stream.ConsumeBool();
  opts.dry_run = stream.ConsumeBool();
  opts.signoff = stream.ConsumeBool();
  opts.signoff_keyid = stream.ConsumeIntegral<unsigned int>();
  opts.signoff_key = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<size_t>());
  opts.signoff_key_len = opts.signoff_key.size();
  opts.signoff_passphrase = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<size_t>());
  opts.signoff_passphrase_len = opts.signoff_passphrase.size();
  opts.signoff_timestamp = stream.ConsumeIntegral<time_t>();
  opts.signoff_expire = stream.ConsumeIntegral<time_t>();
  opts.signoff_reason = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<size_t>());
  opts.signoff_reason_len = opts.signoff_reason.size();
  opts.signoff_email = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<size_t>());
  opts.signoff_email_len = opts.signoff_email.size();
  opts.signoff_name = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<size_t>());
  opts.signoff_name_len = opts.signoff_name.size();
  opts.signoff_committer = stream.ConsumeBool();
  opts.signoff_no_committer = stream.ConsumeBool();
  opts.signoff_no_signer = stream.ConsumeBool();
  opts.signoff_no_timestamp = stream.ConsumeBool();
  opts.signoff_no_expire = stream.ConsumeBool();
  opts.signoff_no_reason = stream.ConsumeBool();
  opts.signoff_no_email = stream.ConsumeBool();
  opts.signoff_no_name = stream.ConsumeBool();
  opts.signoff_no_gpg = stream.ConsumeBool();
  opts.signoff_no_ds = stream.ConsumeBool();
  opts.signoff_no_ed25519 = stream.ConsumeBool();
  opts.signoff_no_rsa = stream.ConsumeBool();
  opts.signoff_no_ecdsa = stream.ConsumeBool();
  opts.signoff_no_annotate = stream.ConsumeBool();
  opts.signoff_no_verify = stream.ConsumeBool();
  opts.signoff_no_check_committer = stream.ConsumeBool();
  opts.signoff_no_check_signer = stream.ConsumeBool();
  opts.signoff_no_check_timestamp = stream.ConsumeBool();
  opts.signoff_no_check_expire = stream.ConsumeBool();
  opts.signoff_no_check_reason = stream.ConsumeBool();
  opts.signoff_no_check_email = stream.ConsumeBool();
  opts.signoff_no_check_name = stream.ConsumeBool();
  opts.signoff_no_check_gpg = stream.ConsumeBool();
  opts.signoff_no_check_ds = stream.ConsumeBool();
  opts.signoff_no_check_ed25519 = stream.ConsumeBool();
  opts.signoff_no_check_rsa = stream.ConsumeBool();
  opts.signoff_no_check_ecdsa = stream.ConsumeBool();
  opts.signoff_no_check_annotate = stream.ConsumeBool();
  opts.signoff_no_check_verify = stream.ConsumeBool();
  opts.signoff_no_check_committer_date = stream.ConsumeBool();
  opts.signoff_no_check_signer_date = stream.ConsumeBool();
  opts.signoff_no_check_timestamp_date = stream.ConsumeBool();
  opts.signoff_no_check_expire_date = stream.ConsumeBool();
  opts.signoff_no_check_reason_date = stream.ConsumeBool();
  opts.signoff_no_check_email_date = stream.ConsumeBool();
  opts.signoff_no_check_name_date = stream.ConsumeBool();
  opts.signoff_no_check_gpg_date = stream.ConsumeBool();
  opts.signoff_no_check_ds_date = stream.ConsumeBool();
  opts.signoff_no_check_ed25519_date = stream.ConsumeBool();
  opts.signoff_no_check_rsa_date = stream.ConsumeBool();
  opts.signoff_no_check_ecdsa_date = stream.ConsumeBool();
  opts.signoff_no_check_annotate_date = stream.ConsumeBool();
  opts.signoff_no_check_verify_date = stream.ConsumeBool();
  opts.signoff_no_check_committer_email = stream.ConsumeBool();
  opts.signoff_no_check_signer_email = stream.ConsumeBool();
  opts.signoff_no_check_timestamp_email = stream.ConsumeBool();
  opts.signoff_no_check_expire_email = stream.ConsumeBool();
  opts.signoff_no_check_reason_email = stream.ConsumeBool();
  opts.signoff_no_check_email_email = stream.ConsumeBool();
  opts.signoff_no_check_name_email = stream.ConsumeBool();
  opts.signoff_no_check_gpg_email = stream.ConsumeBool();
  opts.signoff_no_check_ds_email = stream.ConsumeBool();
  opts.signoff_no_check_ed25519_email = stream.ConsumeBool();
  opts.signoff_no_check_rsa_email = stream.ConsumeBool();
  opts.signoff_no_check_ecdsa_email = stream.ConsumeBool();
  opts.signoff_no_check_annotate_email = stream.ConsumeBool();
  opts.signoff_no_check_verify_email = stream.ConsumeBool();
  opts.signoff_no_check_committer_keyid = stream.ConsumeBool();
  opts.signoff_no_check_signer_keyid = stream.ConsumeBool();
  opts.signoff_no_check_timestamp_keyid = stream.ConsumeBool();
  opts.signoff_no_check_expire_keyid = stream.ConsumeBool();
  opts.signoff_no_check_reason_keyid = stream.ConsumeBool();
  opts.signoff_no_check_email_keyid = stream.ConsumeBool();
  opts.signoff_no_check_name_keyid = stream.ConsumeBool();
  opts.signoff_no_check_gpg_keyid = stream.ConsumeBool();
  opts.signoff_no_check_ds_keyid = stream.ConsumeBool();
  opts.signoff_no_check_ed25519_keyid = stream.ConsumeBool();
  opts.signoff_no_check_rsa_keyid = stream.ConsumeBool();
  opts.signoff_no_check_ecdsa_keyid = stream.ConsumeBool();
  opts.signoff_no_check_annotate_keyid = stream.ConsumeBool();
  opts.signoff_no_check_verify_keyid = stream.ConsumeBool();
  opts.signoff_no_check_committer_name = stream.ConsumeBool();
  opts.signoff_no_check_signer_name = stream.ConsumeBool();
  opts.signoff_no_check_timestamp_name = stream.ConsumeBool();
  opts.signoff_no_check_expire_name = stream.ConsumeBool();
  opts.signoff_no_check_reason_name = stream.ConsumeBool();
  opts.signoff_no_check_email_name = stream.ConsumeBool();
  opts.signoff_no_check_name_name = stream.ConsumeBool();
  opts.signoff_no_check_gpg_name = stream.ConsumeBool();
  opts.signoff_no_check_ds_name = stream.ConsumeBool();
  opts.signoff_no_check_ed25519_name = stream.ConsumeBool();
  opts.signoff_no_check_rsa_name = stream.ConsumeBool();
  opts.signoff_no_check_ecdsa_name = stream.ConsumeBool();
  opts.signoff_no_check_annotate_name = stream.ConsumeBool();
  opts.signoff_no_check_verify_name = stream.ConsumeBool();

  run_sequencer_rebase(&opts);

  return 0;
}