/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/script/runners/cmd.h>
#include <stdio.h>
#include <stdlib.h>

static const char *extensions[] = {".cmd", ".bat"};

static int fn_invoke(const char *script, const char *cwd, const char *fn_name);

static int prepare(const char *script, const char *cwd);
static int build(const char *script, const char *cwd);
static int install(const char *script, const char *cwd);
static int upgrade(const char *script, const char *cwd);
static int uninstall(const char *script, const char *cwd);
static int clean(const char *script, const char *cwd);

GttScriptRunner cmd_sr = {
    extensions, sizeof(extensions) / sizeof(*extensions),
    prepare,    build,
    install,    upgrade,
    uninstall,  clean,
};

int fn_invoke(const char *script, const char *cwd, const char *fn_name) {
  char command[GTT_BUFLEN * 4];
  snprintf(command, GTT_BUFLEN * 4, "cmd.exe /d /c \"cd \"%s\" & \"%s\" %s\"",
           cwd, script, fn_name);

  /* system() on Windows seems to return correct exit status; no need to right
   * shift by 8. */
  return system(command);
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
