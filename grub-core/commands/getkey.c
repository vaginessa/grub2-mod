/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2017  Free Software Foundation, Inc.
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
#include <grub/misc.h>
#include <grub/term.h>
#include <grub/env.h>
#include <grub/command.h>
#include <grub/i18n.h>

GRUB_MOD_LICENSE ("GPLv3+");

static grub_err_t
grub_cmd_getkey (grub_command_t cmd __attribute__ ((unused)),
	      int argc, char **args)

{

  int key;
  char keyenv[20];
  key = grub_getkey ();
  grub_printf ("%d\n", key);
  if (argc == 1)
    {
      grub_snprintf (keyenv, 20, "%d", key);
      grub_env_set (args[0], keyenv);
    }
  return GRUB_ERR_NONE;
}

static grub_command_t cmd;

GRUB_MOD_INIT(getkey)
{
  cmd = grub_register_command ("getkey", grub_cmd_getkey,
			       N_("[VARNAME]"),
			       N_("Return the value of the pressed key. "));
}

GRUB_MOD_FINI(getkey)
{
  grub_unregister_command (cmd);
}
