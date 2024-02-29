
# Prompting Comparison Guide 

This page documents the results and improvements of a different prompting stragy: explicit reasoning based prompting (See [cool_temp]()). We compare the results with the baseline prompts in 
[temp_xml](). Below are the fuzzbench benchmarks that explicit reasoning based prompting further improves upon. 

All results are documented in [prompts_results](). 

Note: when we say "max cov. diff", we compare the results by explicit reasoning based prompting and the temp_xml baseline. In mathematical terms, 
max cov. Diff = max cov. by temp_xml - max cov. by xplicit reasoning based prompting 

  | Benchmarks  | Fuzz Targets |Max Cov. Diff|Model |Prompt history|
| ------------- | ------------- |------------- |------------- |------------- |
|  harfbuzz | ``hb_face_t * hb_subset_preprocess(hb_face_t *)`` |1.6%  | Vertex AI codeBison | |
|  harfbuzz | ``void hb_ot_shape_glyphs_closure(hb_font_t *, hb_buffer_t *, const hb_feature_t *, unsigned int, hb_set_t *)`` |0.5%  | Vertex AI codeBison | |
|  zlib | ``hb_face_t * hb_subset_preprocess(hb_face_t *)`` |1.6%  | Vertex AI codeBison | |



 **harfbuzz results by temp_xml**

<img width="679" alt="Screen Shot 2024-02-28 at 2 51 44 PM" src="https://github.com/sallywang147/llmfz/assets/60257613/39dffe7b-47de-47a2-9dcf-8150b711206d">



 **harfbuzz results by cool_temp**
 
 <img width="659" alt="Screen Shot 2024-02-28 at 3 45 06 PM" src="https://github.com/sallywang147/llmfz/assets/60257613/14a63f0b-4b43-400f-bb1e-c67235ba3a2f">
