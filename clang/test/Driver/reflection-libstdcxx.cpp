// UNSUPPORTED: system-windows

/// libstdc++ has no <meta> that works with our reflection intrinsics, so the
/// one from the resource directory has to come ahead of the libstdc++ headers.

// DEFINE: %{common} = %clangxx %s -### -fsyntax-only \
// DEFINE:   --target=x86_64-unknown-linux-gnu \
// DEFINE:   --sysroot=%S/Inputs/debian_multiarch_tree \
// DEFINE:   -ccc-install-dir %S/Inputs/basic_linux_tree/usr/bin \
// DEFINE:   -resource-dir=%S/Inputs/resource_dir \
// DEFINE:   --gcc-install-dir=%S/Inputs/debian_multiarch_tree/usr/lib/gcc/x86_64-linux-gnu/10

// RUN: %{common} -stdlib=libstdc++ -freflection 2>&1 \
// RUN:   | FileCheck %s --check-prefix=WRAPPERS
// RUN: %{common} -stdlib=libstdc++ -freflection-latest 2>&1 \
// RUN:   | FileCheck %s --check-prefix=WRAPPERS
// WRAPPERS:      "-resource-dir" "[[RESOURCE:[^"]+]]"
// WRAPPERS:      "-internal-isystem" "[[RESOURCE]]{{/|\\\\}}include{{/|\\\\}}libstdcxx_wrappers"
// WRAPPERS-SAME: {{^}} "-internal-isystem" "{{[^"]+}}/usr/lib/gcc/x86_64-linux-gnu/10/../../../../include/c++/10"

// RUN: %{common} -stdlib=libstdc++ 2>&1 \
// RUN:   | FileCheck %s --check-prefix=NO-WRAPPERS
// RUN: %{common} -stdlib=libstdc++ -freflection -fno-reflection 2>&1 \
// RUN:   | FileCheck %s --check-prefix=NO-WRAPPERS
// RUN: %{common} -stdlib=libstdc++ -freflection -nostdinc++ 2>&1 \
// RUN:   | FileCheck %s --check-prefix=NO-WRAPPERS
// RUN: %{common} -stdlib=libstdc++ -freflection -nobuiltininc 2>&1 \
// RUN:   | FileCheck %s --check-prefix=NO-WRAPPERS
// RUN: %{common} -stdlib=libc++ -freflection 2>&1 \
// RUN:   | FileCheck %s --check-prefix=NO-WRAPPERS
// NO-WRAPPERS-NOT: libstdcxx_wrappers
