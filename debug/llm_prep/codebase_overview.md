# LLM-Ready Codebase Overview — 2025-12-18

Project: debug

## Directory Structure

```text
.
├── llm_prep
│   ├── dot_graphs_doxygen
│   │   ├── debug_8h__incl.dot
│   │   └── graph_legend.dot
│   ├── dot_graphs_pyreverse
│   ├── doxygen_output
│   │   ├── html
│   │   │   ├── search
│   │   │   ├── clipboard.js
│   │   │   ├── cookie.js
│   │   │   ├── debug_8h.html
│   │   │   ├── debug_8h.js
│   │   │   ├── debug_8h__incl.dot
│   │   │   ├── debug_8h__incl.map
│   │   │   ├── debug_8h__incl.md5
│   │   │   ├── debug_8h__incl.svg
│   │   │   ├── debug_8h_source.html
│   │   │   ├── doxygen.css
│   │   │   ├── doxygen.svg
│   │   │   ├── doxygen_crawl.html
│   │   │   ├── dynsections.js
│   │   │   ├── files.html
│   │   │   ├── files_dup.js
│   │   │   ├── globals.html
│   │   │   ├── globals_defs.html
│   │   │   ├── graph_legend.dot
│   │   │   ├── graph_legend.html
│   │   │   ├── graph_legend.md5
│   │   │   ├── graph_legend.svg
│   │   │   ├── index.html
│   │   │   ├── jquery.js
│   │   │   ├── menu.js
│   │   │   ├── menudata.js
│   │   │   ├── navtree.css
│   │   │   ├── navtree.js
│   │   │   ├── navtreedata.js
│   │   │   ├── navtreeindex0.js
│   │   │   └── tabs.css
│   │   └── latex
│   │       ├── Makefile
│   │       ├── debug_8h.tex
│   │       ├── debug_8h__incl.dot
│   │       ├── debug_8h__incl.md5
│   │       ├── debug_8h__incl.pdf
│   │       ├── debug_8h_source.tex
│   │       ├── doxygen.sty
│   │       ├── etoc_doxygen.sty
│   │       ├── files.tex
│   │       └── refman.tex
│   ├── codebase_overview.md
│   ├── codebase_stats.txt
│   ├── codebase_structure.txt
│   ├── llm_system_prompt.md
│   ├── project_guidance.md
│   └── tags
├── tests
│   ├── Makefile
│   ├── test_debug_c23.c
│   ├── test_debug_cpp23.cpp
│   ├── test_debug_ndebug_c23.c
│   └── test_debug_ndebug_cpp23.cpp
├── Doxyfile
└── debug.h

9 directories, 55 files
```

## Code Statistics

```text
github.com/AlDanial/cloc v 2.00  T=0.04 s (1286.8 files/s, 382797.7 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
TeX                              6            138            174           3739
CSS                              4            491             66           2642
JavaScript                      18            195            231           2085
HTML                             8             62             35           1926
C++                              2            177            165            771
C                                2            149            159            611
SVG                              3              0             36            288
C/C++ Header                     1             38            120            212
make                             2             25             29            150
Markdown                         3             18              0             76
Text                             1              1              0             65
-------------------------------------------------------------------------------
SUM:                            50           1294           1015          12565
-------------------------------------------------------------------------------
```

## Doxygen (C/C++ Focus)
- Browse interactive docs: `llm_prep/doxygen_output/html/index.html`
- Textual DOT graphs (ideal for pasting to LLM):
  - classBacktraceTestClass__coll__graph.dot (0 KB)
  - classBacktraceTestClass_a4b8ed16ea934e9048e8fe478c8a508bd_icgraph.dot (1 KB)
  - classDataProcessor__coll__graph.dot (2 KB)
  - classDataProcessor_a5043be47141ba8aae70addf7bf1a67b7_icgraph.dot (1 KB)
  - classDataProcessor_a8226b8294438db06d47fdc6bbf0425dc_icgraph.dot (1 KB)
  - classDebuggedClass__coll__graph.dot (1 KB)
  - classDebuggedClass_ab7275e4d708cb34870377849b8916a41_icgraph.dot (1 KB)
  - classDebuggedClass_abb89f767270c24a7512862cd1366e352_icgraph.dot (1 KB)
  - classInstrumentedClassNDEBUG__coll__graph.dot (1 KB)
  - classInstrumentedClassNDEBUG_abdb1cd8d67883ca92e6014c2526fd9f0_icgraph.dot (1 KB)
  - classInstrumentedClass__coll__graph.dot (1 KB)
  - classInstrumentedClass_a2c484a8cbc1ef73c9af067220f7cf659_cgraph.dot (0 KB)
  - classInstrumentedClass_a59098ca37ba1bcbaf4c5d20c46507ef9_icgraph.dot (1 KB)
  - classInstrumentedClass_a866c139ba7c02c418bee6fce3d691a20_cgraph.dot (0 KB)
  - classInstrumentedClass_a8d11c69e337b310f8b5256878c935b5e_icgraph.dot (1 KB)
  - classInstrumentedClass_a9e6a0323d7657ede97503d742bca0172_cgraph.dot (0 KB)
  - debug_8h__dep__incl.dot (1 KB)
  - debug_8h__incl.dot (1 KB)
  - graph_legend.dot (1 KB)
  - structTestStruct__coll__graph.dot (1 KB)
  - test__debug__c23_8c__incl.dot (2 KB)
  - test__debug__c23_8c_a070645fd58a3b0365fbf8025670b6ffd_icgraph.dot (0 KB)
  - test__debug__c23_8c_a1204b683620a0be822cf730bd0ba62bc_cgraph.dot (0 KB)
  - test__debug__c23_8c_a1204b683620a0be822cf730bd0ba62bc_icgraph.dot (0 KB)
  - test__debug__c23_8c_a1ec8bd65f26977c6967fb15496f0d9b7_icgraph.dot (1 KB)
  - test__debug__c23_8c_a236013fe89e8103349a3272b381fedaa_icgraph.dot (0 KB)
  - test__debug__c23_8c_a36e59b0be0bbad85d4b4b42f2188be83_cgraph.dot (1 KB)
  - test__debug__c23_8c_a36e59b0be0bbad85d4b4b42f2188be83_icgraph.dot (0 KB)
  - test__debug__c23_8c_a399d22ae62256fd4eae26659481daa0e_icgraph.dot (0 KB)
  - test__debug__c23_8c_a421d01ced77bf939f3b05b56b63f73e8_icgraph.dot (0 KB)
  - test__debug__c23_8c_a50262936d72a69c82c47f6db7d6f6012_cgraph.dot (0 KB)
  - test__debug__c23_8c_a50262936d72a69c82c47f6db7d6f6012_icgraph.dot (0 KB)
  - test__debug__c23_8c_a630493237da7c4b14a0ff35df769c1b0_icgraph.dot (0 KB)
  - test__debug__c23_8c_a6638f20a4f40a1d47bd800861efe5ca9_icgraph.dot (0 KB)
  - test__debug__c23_8c_a71f8d45958443cd5674440c49ef24ddb_icgraph.dot (1 KB)
  - test__debug__c23_8c_a729bda48162c78822de3814a8f84116e_icgraph.dot (0 KB)
  - test__debug__c23_8c_a762d2c3daf66232299289484c0d942b5_icgraph.dot (0 KB)
  - test__debug__c23_8c_a840291bc02cba5474a4cb46a9b9566fe_cgraph.dot (6 KB)
  - test__debug__c23_8c_a841bd8b53d75a1d7b720daaa33deaf23_icgraph.dot (0 KB)
  - test__debug__c23_8c_a90cc493d0a2d314a6dab34b1291719b0_icgraph.dot (0 KB)
  - test__debug__c23_8c_a9f94bc8cc6dd6b8b67078d3bb93cc228_icgraph.dot (0 KB)
  - test__debug__c23_8c_aae7227ee947675edb35201c4b6fe5861_cgraph.dot (0 KB)
  - test__debug__c23_8c_aae7227ee947675edb35201c4b6fe5861_icgraph.dot (0 KB)
  - test__debug__c23_8c_ab5dd89928bb6a9153783e528da4d7e73_icgraph.dot (1 KB)
  - test__debug__c23_8c_abe9dd1824989d6d407f1d61f9b95146b_icgraph.dot (0 KB)
  - test__debug__c23_8c_ac99394a87dbc4834c706e76a021bf241_icgraph.dot (1 KB)
  - test__debug__c23_8c_aee014ef70f7d824ea263859fc89adbc7_icgraph.dot (0 KB)
  - test__debug__c23_8c_af3151e06f0c701ba63c3205ab565fcb4_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp__incl.dot (3 KB)
  - test__debug__cpp23_8cpp_a005c9200a65974f91d0d903625d3ec81_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a0bfe72391fa06ea16c12d91427413d0f_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a0cef31a8b5b34a5320b50f81fdc88e89_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a1ae401010958a8bce65f86801524642c_icgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_a28b145ffc7317de2c2666b4aec97a60e_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a42688af68a552775443f26f2eb3a19b0_icgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_a520b15765a9e0245a810153dc5e94861_cgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a520b15765a9e0245a810153dc5e94861_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a633b46bbb31ce17592e22a198b714df1_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a6ab12c923524af9709392c92cc4cd96d_cgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_a6ab12c923524af9709392c92cc4cd96d_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a6c6500426cd1f9a88e143e09532ccc2d_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a853b304e67e6c661d4b0bc99047c0064_cgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a853b304e67e6c661d4b0bc99047c0064_icgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_a926c42003f0cee36771df77eee41efbb_cgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a926c42003f0cee36771df77eee41efbb_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_a97c8f500cde880afe746443238a74dcc_cgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_a97c8f500cde880afe746443238a74dcc_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_ab2cc58863e7ba345c76707bc3a6f8f99_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_ab72aba90868d74c3ae9bf25bdb34585f_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_ac8373f4e2b5e1fc276765fc28a8b6546_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_ad3789cb00bb02eb8960f4c281f85cb91_cgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_ad3789cb00bb02eb8960f4c281f85cb91_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_ad73831b31c182649eb8f3c580532c05a_icgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_ae66f6b31b5ad750f1fe042a706a4e3d4_cgraph.dot (8 KB)
  - test__debug__cpp23_8cpp_aee1af3519818ccd0f1eb48d707d3c1de_icgraph.dot (1 KB)
  - test__debug__cpp23_8cpp_aefeb3adbc285b15e2a880c26b6ff21d0_icgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_afdee567b7a327af3b157029c88f8c218_cgraph.dot (0 KB)
  - test__debug__cpp23_8cpp_afdee567b7a327af3b157029c88f8c218_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c__incl.dot (2 KB)
  - test__debug__ndebug__c23_8c_a0b1065a5e291440abed7609a9960a2e0_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_a73ce260db71fba16eeecb57458651209_icgraph.dot (1 KB)
  - test__debug__ndebug__c23_8c_a840291bc02cba5474a4cb46a9b9566fe_cgraph.dot (4 KB)
  - test__debug__ndebug__c23_8c_a87ab7efab29391dc5cf772da1f581584_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_aa5b41e59df8f5ff13fb8638e09a3b3dc_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_aaa9dbffad342361957b2bbad0c5ded4b_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_ac70f8198234849c9ccc782a21ec970ed_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_ad168b038cd0b62e64f6c1e7204cb0ffd_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_ae4239a57b66cf8b6cd557eeba7e87be8_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_ae8306f806dfb664363b3c4d75bc9248c_cgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_ae8306f806dfb664363b3c4d75bc9248c_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_aea4efc18bc3333e10e42b7e690f2c4d9_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_aee3c2168564f50e7659cb1342a519a2a_icgraph.dot (0 KB)
  - test__debug__ndebug__c23_8c_afebcb7041408032d210cd656aefea651_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp__incl.dot (3 KB)
  - test__debug__ndebug__cpp23_8cpp_a01c1852611202130ff4da82279419542_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_a036e6fe506b4e091fdd4afed11f4324e_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_a4bcc0216a15bdf4375a9238c508ee86d_icgraph.dot (1 KB)
  - test__debug__ndebug__cpp23_8cpp_a70286f88f0184f920d7925a0294bfff7_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_aa8bd18593d35cc10789a7f0ca6899d7c_cgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_aa8bd18593d35cc10789a7f0ca6899d7c_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_abe35d450753298b8bc0860cf48ef96d1_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_ad526b54e826f658ccf773671a5187f34_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_ad7fb3a19edb49f92bae516f41796f97d_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_ae1bb52038385591c2d583cbc1dc0b85d_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_ae66f6b31b5ad750f1fe042a706a4e3d4_cgraph.dot (4 KB)
  - test__debug__ndebug__cpp23_8cpp_ae89bb12596822343c293088e48b82f99_icgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_afe237ae653fee1cd296bb801d4f01ae9_cgraph.dot (0 KB)
  - test__debug__ndebug__cpp23_8cpp_afe237ae653fee1cd296bb801d4f01ae9_icgraph.dot (0 KB)

## Tags File
- `llm_prep/tags` generated for symbol navigation.

## Generated LLM Files
- `llm_system_prompt.md`: Copy-paste as system prompt for sessions.
- `project_guidance.md`: Best practices, tools, QA, etc.

## How to Use with an LLM
- Paste this entire file as initial context.
- For details, paste contents of key `.dot` files (e.g., main call graph).
- View HTML output for visual graphs.
