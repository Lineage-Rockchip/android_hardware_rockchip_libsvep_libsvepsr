package libsvepsr_conditional_compile

import (
    "android/soong/android"
    "android/soong/cc"
    "fmt"
    "strings"
)

var SUPPORT_TARGET_PLATFORM = [...]string{
    "rk356x",
    "rk3588",
    "rk3576",
}

func init() {
    fmt.Println("libsvepsr want to conditional Compile")
    android.RegisterModuleType("cc_libsvepsr_prebuilt_library_shared", LibsvepsrFactory)
}

func LibsvepsrFactory() (android.Module) {
    module := cc.PrebuiltSharedLibraryFactory()
    android.AddLoadHook(module, LibsvepsrPrebuiltLibrary)
    return module
}

func LibsvepsrPrebuiltLibrary(ctx android.LoadHookContext) {

    type props struct {
        Multilib struct {
            Lib64 struct {
                Srcs []string
            }
            Lib32 struct {
                Srcs []string
            }
        }
        Export_include_dirs []string
    }
    p := &props{}

    p.Multilib.Lib64.Srcs = getLibsvepsrLibrary(ctx, "arm64-v8a")
    p.Multilib.Lib32.Srcs = getLibsvepsrLibrary(ctx, "armeabi-v7a")
    p.Export_include_dirs = getLibsvepsrHeader(ctx)
    ctx.AppendProperties(p)
}

func checkEnabled(ctx android.LoadHookContext) bool {
    var soc string = getTargetSoc(ctx)
    for i := 0; i < len(SUPPORT_TARGET_PLATFORM); i++ {
        if (strings.EqualFold(SUPPORT_TARGET_PLATFORM[i], soc)) {
            fmt.Println("libsvepsr enabled on " + soc)
            return true
        }
    }
    fmt.Println("libsvepsr disabled on " + soc)
    return false
}

func getLibsvepsrLibrary(ctx android.LoadHookContext, arch string) ([]string) {
    var src []string
    var soc string = getTargetSoc(ctx)
    var prefix string = soc

    if (!checkEnabled(ctx)) {
        prefix = "rk356x"
    }

    // fmt.Println("soc=" + soc + " arch=" + arch)

    src = append(src,  "lib/Android/" + prefix + "/" + arch + "/libsvepsr.so")

    return src
}

func getLibsvepsrHeader(ctx android.LoadHookContext) ([]string) {
    var src []string
    var soc string = getTargetSoc(ctx)
    var prefix string = soc

    if (!checkEnabled(ctx)) {
        prefix = "rk356x"
    }

    src = append(src, "lib/Android/" + prefix + "/include/")

    return src
}

func getTargetSoc(ctx android.LoadHookContext) (string) {
    var target_board_platform string = ctx.AConfig().Getenv("TARGET_BOARD_PLATFORM")
    return target_board_platform
}