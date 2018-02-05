/* bqcat.c - command to store the contents of a file in a variable */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2018  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <grub/dl.h>
#include <grub/file.h>
#include <grub/env.h>
#include <grub/command.h>

GRUB_MOD_LICENSE ("GPLv3+");

static grub_err_t
grub_cmd_bqcat (grub_command_t cmd __attribute__ ((unused)), int argc, char **args)
{
  grub_file_t file;
  grub_ssize_t size;
  grub_ssize_t done = 0;
  char* buffer;

  if (argc != 2)
    return grub_error (GRUB_ERR_BAD_ARGUMENT, N_("filename and variable name expected"));

  file = grub_file_open (args[0]);
  if (! file)
    return grub_errno;

  buffer = grub_malloc(file->size + 1);

  while ((size = grub_file_read (file, buffer + done, file->size - done)) > 0)
    {
      done += size;
    }

  buffer[done] = '\0';
  grub_env_set (args[1], buffer);
  grub_file_close (file);
  grub_free(buffer);

  return 0;
}

static grub_command_t cmd;

GRUB_MOD_INIT(bqcat)
{
  cmd = grub_register_command ("bqcat", grub_cmd_bqcat, N_("FILE VARIABLE"), N_("Store the contents of a file in a variable."));
}

GRUB_MOD_FINI(bqcat)
{
  grub_unregister_command (cmd);
}