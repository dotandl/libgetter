/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/script/runners/sh.h>
#include <stdio.h>
#include <stdlib.h>

/* On macOS, WEXITSTATUS macro is (probably) broken. So I use a new,
 * OS-independent macro already combined with system() call here. */
#define gtt_shell_command(cmd) ((system((cmd)) & 0xff00) >> 8)

#define GTT_SH_SCRIPT_RUNNER_SHELL "bash"

static const char *extensions[] = {".sh"};

static int fn_invoke(const char *script, const char *cwd, const char *fn_name);

static int prepare(const char *script, const char *cwd);
static int build(const char *script, const char *cwd);
static int install(const char *script, const char *cwd);
static int upgrade(const char *script, const char *cwd);
static int uninstall(const char *script, const char *cwd);
static int clean(const char *script, const char *cwd);

GttScriptRunner sh_sr = {
    extensions, sizeof(extensions) / sizeof(*extensions),
    prepare,    build,
    install,    upgrade,
    uninstall,  clean,
};

int fn_invoke(const char *script, const char *cwd, const char *fn_name) {
  char command[GTT_BUFLEN * 4];
  snprintf(command, GTT_BUFLEN * 4, "%s -c \"(cd '%s'; source '%s'; %s)\"",
           GTT_SH_SCRIPT_RUNNER_SHELL, cwd, script, fn_name);

  return gtt_shell_command(command);
}

int prepare(const char *script, const char *cwd) {
  return fn_invoke(script, cwd, "prepare");
}
int build(const char *script, const char *cwd) {
  return fn_invoke(script, cwd, "build");
}
int install(const char *script, const char *cwd) {
  return fn_invoke(script, cwd, "install");
}
int upgrade(const char *script, const char *cwd) {
  return fn_invoke(script, cwd, "upgrade");
}
int uninstall(const char *script, const char *cwd) {
  return fn_invoke(script, cwd, "uninstall");
}
int clean(const char *script, const char *cwd) {
  return fn_invoke(script, cwd, "clean");
}
