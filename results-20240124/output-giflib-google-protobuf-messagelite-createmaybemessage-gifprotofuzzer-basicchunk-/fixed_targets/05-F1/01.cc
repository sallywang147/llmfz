 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "ProtoToGif.h"
#include "gifProtoFuzzer.pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gifProtoFuzzer::BasicChunk chunk;
  gifProtoFuzzer::BasicChunk* chunk_ptr = &chunk;
  gifProtoFuzzer::BasicChunk* chunk_ptr2 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr3 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr4 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr5 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr6 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr7 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr8 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr9 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr10 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr11 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr12 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr13 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr14 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr15 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr16 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr17 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr18 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr19 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr20 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr21 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr22 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr23 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr24 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr25 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr26 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr27 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr28 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr29 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr30 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr31 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr32 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr33 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr34 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr35 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr36 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr37 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr38 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr39 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr40 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr41 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr42 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr43 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr44 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr45 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr46 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr47 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr48 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr49 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr50 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr51 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr52 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr53 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr54 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr55 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr56 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr57 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr58 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr59 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr60 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr61 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr62 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr63 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr64 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr65 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr66 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr67 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr68 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr69 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr70 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr71 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr72 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr73 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr74 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr75 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr76 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr77 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr78 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr79 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr80 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr81 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr82 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr83 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr84 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr85 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr86 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr87 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr88 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr89 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr90 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr91 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr92 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr93 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr94 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr95 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr96 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr97 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr98 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr99 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr100 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr101 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr102 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr103 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr104 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr105 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr106 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr107 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr108 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr109 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr110 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr111 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr112 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr113 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr114 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr115 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr116 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr117 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr118 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr119 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr120 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr121 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr122 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr123 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr124 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr125 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr126 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr127 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr128 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr129 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr130 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr131 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr132 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr133 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr134 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr135 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr136 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr137 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr138 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr139 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr140 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr141 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr142 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr143 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr144 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr145 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr146 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr147 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr148 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr149 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr150 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr151 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr152 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr153 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr154 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr155 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr156 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr157 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr158 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr159 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr160 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr161 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr162 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr163 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr164 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr165 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr166 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr167 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr168 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr169 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr170 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr171 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr172 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr173 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr174 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr175 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr176 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr177 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr178 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr179 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr180 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr181 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr182 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr183 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr184 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr185 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr186 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr187 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr188 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr189 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr190 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr191 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr192 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr193 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr194 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr195 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr196 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr197 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr198 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr199 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr200 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr201 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr202 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr203 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr204 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr205 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr206 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr207 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr208 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr209 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr210 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr211 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr212 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr213 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr214 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr215 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr216 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr217 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr218 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr219 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr220 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr221 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr222 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr223 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr224 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr225 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr226 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr227 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr228 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr229 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr230 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr231 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr232 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr233 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr234 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr235 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr236 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr237 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr238 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr239 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr240 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr241 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr242 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr243 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr244 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr245 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr246 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr247 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr248 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr249 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr250 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr251 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr252 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr253 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr254 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr255 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr256 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr257 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr258 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr259 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr260 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr261 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr262 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr263 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr264 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr265 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr266 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr267 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr268 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr269 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr270 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr271 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr272 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr273 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr274 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr275 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr276 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr277 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr278 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr279 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr280 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr281 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr282 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr283 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr284 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr285 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr286 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr287 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr288 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr289 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr290 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr291 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr292 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr293 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr294 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr295 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr296 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr297 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr298 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr299 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr300 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr301 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr302 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr303 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr304 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr305 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr306 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr307 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr308 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr309 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr310 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr311 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr312 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr313 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr314 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr315 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr316 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr317 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr318 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr319 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr320 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr321 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr322 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr323 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr324 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr325 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr326 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr327 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr328 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr329 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr330 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr331 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr332 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr333 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr334 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr335 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr336 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr337 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr338 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr339 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr340 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr341 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr342 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr343 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr344 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr345 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr346 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr347 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr348 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr349 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr350 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr351 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr352 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr353 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr354 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr355 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr356 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr357 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr358 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr359 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr360 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr361 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr362 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr363 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr364 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr365 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr366 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr367 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr368 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr369 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr370 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr371 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr372 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr373 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr374 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr375 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr376 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr377 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr378 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr379 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr380 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr381 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr382 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr383 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr384 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr385 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr386 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr387 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr388 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr389 = chunk_ptr;
  gifProtoFuzzer::BasicChunk* chunk_ptr390 = chunk_