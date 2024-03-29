/* Copyright (C) 2009 Trend Micro Inc.
 * All rights reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation.
 */

#include "shared.h"
#include "sec.h"

/** Prototypes **/

/* b64 function prototypes */
char *decode_base64(const char *src);
char *encode_base64(int size, char *src);

/* Read any input from the user (stdin) */
char *read_from_user(void);

/* Add or remove an agent */
int add_agent(void);
int remove_agent(void);

/* Extract or import a key */
int k_extract(const char *cmdextract);
int k_import(const char *cmdimport);
int k_bulkload(const char *cmdbulk);

/* Validation functions */
int OS_IsValidName(const char *u_name);
int OS_IsValidID(const char *id);
int IDExist(const char *id);
int NameExist(const char *u_name);
char *getFullnameById(const char *id);
char *OS_AddNewAgent(const char *name, const char *ip, const char *id);

/* Print available agents */
int print_agents(int print_status, int active_only, int csv_output);
int list_agents(int cmdlist);

/* Clear a line */
char *chomp(char *str);

/* Shared variables */
extern int restart_necessary;
extern time_t time1;
extern time_t time2;
extern time_t time3;
extern long int rand1;
extern long int rand2;
extern fpos_t fp_pos;

/* Internal defines */
#define USER_SIZE       514
#define FILE_SIZE       257
#define STR_SIZE        66

/* Internal strings */
#define QUIT                "\\q"

/* Print agents */
#define PRINT_AVAILABLE     "\nAvailable agents: \n"
#define PRINT_AGENT         "   ID: %s, Name: %s, IP: %s\n"
#define PRINT_AGENT_STATUS  "   ID: %s, Name: %s, IP: %s, %s\n"

/* Add new agent */
#define ADD_NEW         "\n- Adding a new agent"\
                        " (use '\\q' to return to the main menu).\n"\
                        "  Please provide the following:\n"
#define ADD_NAME        "   * A name for the new agent: "
#define ADD_IP          "   * The IP Address of the new agent: "
#define ADD_ID          "   * An ID for the new agent[%s]: "
#define AGENT_INFO      "Agent information:\n   ID:%s\n   Name:%s\n   " \
                        "IP Address:%s\n\n"
#define ADD_CONFIRM     "Confirm adding it?(y/n): "
#define AGENT_ADD       "Agent added.\n"
#define ADDED           "Added.\n"
#define ADD_NOT         "Not Adding.\n"
#define PRESS_ENTER     "** Press ENTER to return to the main menu.\n"
#define MUST_RESTART    "\n** You must restart OSSEC for your changes" \
                        " to take effect.\n\n"

/* Add errors */
#define ADD_ERROR_ID    "\n** ID '%s' already present. They must be unique.\n\n"
#define ADD_ERROR_NAME  "\n** Name '%s' already present. Please enter a new name.\n\n"
#define IP_ERROR        "\n** Invalid IP '%s'. Please enter a valid IP Address.\n\n"
#define NO_AGENT        "\n** No agent available. You need to add one first.\n"
#define NO_ID           "\n** Invalid ID '%s' given. ID is not present.\n"
#define NO_KEY          "\n** Invalid authentication key. Starting over again.\n"
#define INVALID_ID      "\n** Invalid ID '%s' given. ID must be numeric (max 8 digits).\n\n"
#define INVALID_NAME    "\n** Invalid name '%s' given. Name must contain only alphanumeric characters (min=2, max=32).\n\n"
#define NO_DEFAULT      "\n** Could not get default ID. Ran out of IDs to try with a max of '%d'. Either need to raise max agents or clean out client.keys.\n\n"

/* Remove agent */
#define REMOVE_ID       "Provide the ID of the agent to be removed (or '\\q' to quit): "
#define REMOVE_CONFIRM  "Confirm deleting it?(y/n): "
#define REMOVE_DONE     "Agent '%s' removed.\n"
#define REMOVE_NOT      "Not removing.\n"

/* Import agent */
#define IMPORT_KEY      "\n* Provide the Key generated by the server.\n" \
                        "* The best approach is to cut and paste it.\n" \
                        "*** OBS: Do not include spaces or new lines.\n\n" \
                        "Paste it here (or '\\q' to quit): "

/* Extract key */
#define EXTRACT_KEY     "Provide the ID of the agent to extract " \
                        "the key (or '\\q' to quit): "
#define EXTRACT_MSG     "\nAgent key information for '%s' is: \n%s\n"


/* Common errors */
#define ERROR_KEYS      "Unable to handle keys file. Exiting.\n"
#define EXTRACT_ERROR   "Unable to extract agent key.\n"
#define INPUT_LARGE     ARGV0 ": Input too large. Not adding it.\n"
#define EXIT            ARGV0 ": Exiting.\n"

#define BANNER          "\n****************************************" \
                        "\n* %s %s Agent manager.     *" \
                        "\n* The following options are available: *" \
                        "\n****************************************\n"

#define BANNER_OPT      "   (A)dd an agent (A).\n" \
                        "   (E)xtract key for an agent (E).\n" \
                        "   (L)ist already added agents (L).\n" \
                        "   (R)emove an agent (R).\n" \
                        "   (Q)uit.\n" \
                        "Choose your action: A,E,L,R or Q: "

#define BANNER_CLIENT   "   (I)mport key from the server (I).\n" \
                        "   (Q)uit.\n" \
                        "Choose your action: I or Q: "

/* WIN32 errors */
#define CONF_ERROR      ARGV0 ": Could not read (%s) (Make sure config exists and executable is running with Administrative priviliges).\n"
#define GMF_ERROR       ARGV0 ": Could not run GetModuleFileName.\n"
#define GMF_BUFF_ERROR  ARGV0 ": Could not get path because it is too long and was shrunk by (%d) characters with a max of (%d).\n"
#define GMF_UNKN_ERROR  ARGV0 ": Could not run GetModuleFileName which returned (%ld).\n"

/* Do we chroot? */
int willchroot;

