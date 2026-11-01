#!/bin/bash

# ============================================================
#  Linux File Analysis and Inspection Tool
#  Features: File Type, File Info & Permissions, Strings
# ============================================================

# ---------- Colors (makes the output easier to read) --------
RED='\033[0;31m'       # For errors
GREEN='\033[0;32m'     # For success messages
CYAN='\033[0;36m'      # For section headers
YELLOW='\033[1;33m'    # For prompts and highlights
BOLD='\033[1m'         # Bold text
RESET='\033[0m'        # Reset back to normal color

# ---------- Global variable to remember the last used file --------
# Starts empty — gets filled the first time the user enters a file path
CURRENT_FILE=""

# ============================================================
#  FUNCTION: show_menu
#  Displays the main menu to the user
# ============================================================
show_menu() {
    clear  # Clear the terminal screen for a clean look

    echo -e "${CYAN}${BOLD}"
    echo "  ╔══════════════════════════════════════════════╗"
    echo "  ║    Linux File Analysis & Inspection Tool     ║"
    echo "  ╠══════════════════════════════════════════════╣"
    echo "  ║                                              ║"
    echo "  ║   1.  Identify File Type                     ║"
    echo "  ║   2.  Display File Info & Permissions        ║"
    echo "  ║   3.  Extract Readable Strings               ║"
    echo "  ║   4.  Change Loaded File                     ║"
    echo "  ║   5.  Exit                                   ║"
    echo "  ║                                              ║"
    echo "  ╚══════════════════════════════════════════════╝"
    echo -e "${RESET}"

    # Show which file is currently loaded (or a hint if none yet)
    if [[ -n "$CURRENT_FILE" ]]; then
        echo -e "  ${BOLD}Loaded File :${RESET} ${GREEN}$CURRENT_FILE${RESET}"
    else
        echo -e "  ${BOLD}Loaded File :${RESET} ${YELLOW}None  (you will be asked when you pick option 1, 2 or 3)${RESET}"
    fi
    echo ""
}

# ============================================================
#  FUNCTION: ask_for_new_file
#  Prompts the user to enter a new file path with a helpful hint
#  Sets the global $FILEPATH and $CURRENT_FILE variables
# ============================================================
ask_for_new_file() {
    # Show current directory as a hint so user knows where they are
    echo -e "  ${BOLD}Hint — You are currently in:${RESET} ${CYAN}$(pwd)${RESET}"
    echo -e "  ${BOLD}Hint — Full path example  :${RESET} ${CYAN}/home/kali/Desktop/myfile.txt${RESET}"
    echo ""
    echo -e "${YELLOW}  Enter the full path to the file:${RESET}"
    read -rp "  > " FILEPATH

    # Check if the user left the input empty
    if [[ -z "$FILEPATH" ]]; then
        echo -e "${RED}  [ERROR] No file path entered. Please try again.${RESET}"
        return 1
    fi

    # Check if the file actually exists at the given path
    if [[ ! -f "$FILEPATH" ]]; then
        echo -e "${RED}  [ERROR] File not found: $FILEPATH${RESET}"
        echo -e "  ${YELLOW}Tip: Make sure you typed the full path correctly.${RESET}"
        return 1
    fi

    # Save it so we remember it for next time
    CURRENT_FILE="$FILEPATH"
    echo -e "  ${GREEN}✔ File loaded and remembered!${RESET}"
    echo ""
    return 0
}

# ============================================================
#  FUNCTION: get_filename
#  If a file is already remembered, asks the user whether to
#  reuse it or switch to a different one.
#  Always sets the global $FILEPATH variable.
# ============================================================
get_filename() {
    # Check if we already have a file loaded from a previous run
    if [[ -n "$CURRENT_FILE" ]]; then
        echo -e "  ${BOLD}Currently loaded file:${RESET}"
        echo -e "  ${GREEN}→ $CURRENT_FILE${RESET}"
        echo ""
        echo -e "  ${YELLOW}Use this file? [Press Enter = Yes  |  N = Change file]:${RESET}"
        read -rp "  > " REUSE
        echo ""

        # If user typed N or n — ask for a new file
        if [[ "$REUSE" =~ ^[Nn]$ ]]; then
            ask_for_new_file || return 1
        else
            # User pressed Enter (or anything else) — reuse the remembered file
            FILEPATH="$CURRENT_FILE"
        fi
    else
        # No file loaded yet — ask for one
        ask_for_new_file || return 1
    fi

    return 0
}

# ============================================================
#  FUNCTION: identify_file_type
#  Uses the 'file' command to detect what kind of file it is
# ============================================================
identify_file_type() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  IDENTIFY FILE TYPE  ━━━${RESET}"
    echo ""

    # Ask user for the file path (calls get_filename function above)
    get_filename || return  # if get_filename fails, stop and return to menu

    echo ""
    echo -e "${GREEN}[+] Running: file \"$FILEPATH\"${RESET}"
    echo ""

    # --- Basic file type ---
    # The 'file' command reads the file's content (not just the name)
    # and reports what kind of file it really is
    echo -e "${BOLD}  File Type:${RESET}"
    file "$FILEPATH"

    echo ""

    # --- More detailed MIME type ---
    # MIME type is like a universal label (e.g., text/plain, image/png)
    # The -b flag means "brief" (don't repeat the filename)
    # The --mime-type flag gives the internet-standard type name
    echo -e "${BOLD}  MIME Type:${RESET}"
    file -b --mime-type "$FILEPATH"

    echo ""
    echo -e "${BOLD}  Character Encoding:${RESET}"
    # --mime-encoding tells us if it's UTF-8, binary, etc.
    file -b --mime-encoding "$FILEPATH"

    echo ""
}

# ============================================================
#  FUNCTION: display_file_info
#  Uses 'stat' and 'ls' to show file details and permissions
# ============================================================
display_file_info() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  FILE INFO & PERMISSIONS  ━━━${RESET}"
    echo ""

    get_filename || return

    echo ""

    # --- Section 1: Human-Readable Permissions using ls -lh ---
    # ls   = list files
    # -l   = long format (shows permissions, owner, size, date)
    # -h   = human-readable sizes (KB, MB instead of raw bytes)
    echo -e "${GREEN}[+] Running: ls -lh \"$FILEPATH\"${RESET}"
    echo ""
    echo -e "${BOLD}  Permissions & Ownership:${RESET}"

    # We pipe through awk to format the output more clearly
    ls -lh "$FILEPATH"

    echo ""

    # --- Explain what the permission string means ---
    # Get just the permission bits (first column from ls -l)
    PERMS=$(ls -l "$FILEPATH" | awk '{print $1}')
    echo ""
    echo -e "  ${BOLD}Permission String Breakdown: ${YELLOW}$PERMS${RESET}"
    echo ""
    printf "  %-16s %s\n" "Position  1   :" "File type         ( - = regular file,  d = directory )"
    printf "  %-16s %s\n" "Positions 2-4 :" "Owner permissions ( r = read,  w = write,  x = execute )"
    printf "  %-16s %s\n" "Positions 5-7 :" "Group permissions ( r = read,  w = write,  x = execute )"
    printf "  %-16s %s\n" "Positions 8-10:" "Others permission ( r = read,  w = write,  x = execute )"
    echo ""

    echo ""

    # --- Section 2: Detailed stats using stat ---
    # 'stat' shows much more detail than ls:
    # file size in bytes, block size, inode number, all three timestamps, etc.
    echo -e "${GREEN}[+] Running: stat \"$FILEPATH\"${RESET}"
    echo ""
    echo -e "${BOLD}  Detailed File Statistics:${RESET}"
    echo "  ──────────────────────────────────────────────────────────────────"

    # We call stat -c for each field separately so we can add
    # a description on the same line explaining what it means

    printf "  %-18s %-30s %s\n" \
        "File:" \
        "$(stat -c '%n' "$FILEPATH")" \
        "<- name of the file"

    printf "  %-18s %-30s %s\n" \
        "Size:" \
        "$(stat -c '%s' "$FILEPATH") bytes" \
        "<- actual content size in bytes"

    printf "  %-18s %-30s %s\n" \
        "Blocks Used:" \
        "$(stat -c '%b' "$FILEPATH")" \
        "<- disk blocks allocated (Linux stores in chunks)"

    printf "  %-18s %-30s %s\n" \
        "IO Block:" \
        "$(stat -c '%B' "$FILEPATH") bytes" \
        "<- size of each block Linux reads at once"

    printf "  %-18s %-30s %s\n" \
        "File Type:" \
        "$(stat -c '%F' "$FILEPATH")" \
        "<- regular file, directory, symlink, etc."

    printf "  %-18s %-30s %s\n" \
        "Inode:" \
        "$(stat -c '%i' "$FILEPATH")" \
        "<- Linux's internal unique ID for this file"

    printf "  %-18s %-30s %s\n" \
        "Hard Links:" \
        "$(stat -c '%h' "$FILEPATH")" \
        "<- how many names point to this file"

    echo "  ──────────────────────────────────────────────────────────────────"

    printf "  %-18s %-30s %s\n" \
        "Last Accessed:" \
        "$(stat -c '%x' "$FILEPATH")" \
        "<- last time the file was opened/read"

    printf "  %-18s %-30s %s\n" \
        "Last Modified:" \
        "$(stat -c '%y' "$FILEPATH")" \
        "<- last time the file content was changed"

    printf "  %-18s %-30s %s\n" \
        "Last Changed:" \
        "$(stat -c '%z' "$FILEPATH")" \
        "<- last time permissions or metadata changed"

    printf "  %-18s %-30s %s\n" \
        "Created (Birth):" \
        "$(stat -c '%w' "$FILEPATH")" \
        "<- when the file was first created"

    echo "  ──────────────────────────────────────────────────────────────────"

    echo ""
}

# ============================================================
#  FUNCTION: extract_strings
#  Uses the 'strings' command to pull readable text from a file
# ============================================================
extract_strings() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  EXTRACT READABLE STRINGS  ━━━${RESET}"
    echo ""

    get_filename || return

    echo ""

    # Ask user for minimum string length
    # Longer = fewer results but more meaningful words
    # Shorter = more results including fragments
    echo -e "${YELLOW}Enter minimum string length to extract (default is 4):${RESET}"
    read -p "  > " MIN_LEN

    # If the user just pressed Enter without typing a number,
    # use the default value of 4
    if [[ -z "$MIN_LEN" ]]; then
        MIN_LEN=4
    fi

    # Make sure the input is actually a number
    if ! [[ "$MIN_LEN" =~ ^[0-9]+$ ]]; then
        echo -e "${RED}[ERROR] Please enter a valid number.${RESET}"
        return
    fi

    echo ""

    # 'strings' scans a file for sequences of printable characters
    # -n sets the minimum number of characters a sequence must have
    echo -e "${GREEN}[+] Running: strings -n $MIN_LEN \"$FILEPATH\"${RESET}"
    echo ""

    # Count how many strings were found before showing them
    STRING_COUNT=$(strings -n "$MIN_LEN" "$FILEPATH" | wc -l)
    echo -e "${BOLD}  Total readable strings found: ${YELLOW}$STRING_COUNT${RESET}"
    echo ""

    # Now show a sub-menu for how to display the results
    echo "  How would you like to view the strings?"
    echo "  ┌─────────────────────────────────────┐"
    echo "  │  a. Show all strings (scrollable)   │"
    echo "  │  b. Show first 20 strings only      │"
    echo "  │  c. Search within strings           │"
    echo "  └─────────────────────────────────────┘"
    read -p "  Choice [a/b/c]: " VIEW_CHOICE

    echo ""
    echo -e "${BOLD}  Extracted Strings:${RESET}"
    echo "  ─────────────────────────────────────"

    case "$VIEW_CHOICE" in
        a|A)
            # 'less' lets the user scroll through many lines with arrow keys
            # Press 'q' to quit the less viewer
            strings -n "$MIN_LEN" "$FILEPATH" | less
            ;;
        b|B)
            # 'head -20' shows only the first 20 lines
            strings -n "$MIN_LEN" "$FILEPATH" | head -20
            echo ""
            echo -e "  ${YELLOW}(Showing first 20 of $STRING_COUNT strings)${RESET}"
            ;;
        c|C)
            echo -e "${YELLOW}  Enter keyword to search for inside strings:${RESET}"
            read -p "  > " KEYWORD

            if [[ -z "$KEYWORD" ]]; then
                echo -e "${RED}  [ERROR] No keyword entered.${RESET}"
                return
            fi

            # Pipe strings output into grep to filter by keyword
            # -i = case-insensitive, --color=always = highlight the match
            RESULTS=$(strings -n "$MIN_LEN" "$FILEPATH" | grep -i --color=always "$KEYWORD")

            if [[ -z "$RESULTS" ]]; then
                echo -e "${RED}  No matches found for: \"$KEYWORD\"${RESET}"
            else
                echo "$RESULTS"
            fi
            ;;
        *)
            echo -e "${RED}  Invalid choice. Showing first 20 strings by default.${RESET}"
            strings -n "$MIN_LEN" "$FILEPATH" | head -20
            ;;
    esac

    echo ""
}

# ============================================================
#  MAIN PROGRAM LOOP
#  This keeps the menu showing until the user chooses Exit
# ============================================================
main() {
    # Welcome banner (shown only once at start)
    echo -e "${CYAN}${BOLD}"
    echo "  ┌─────────────────────────────────────────────────┐"
    echo "  │  Welcome to the Linux File Analysis Tool  v1.0  │"
    echo "  │  Built with Bash | Linux Programming Lab        │"
    echo "  └─────────────────────────────────────────────────┘"
    echo -e "${RESET}"
    sleep 1  # pause 1 second so the user can read it

    # 'while true' means loop forever until we 'break' or 'exit'
    while true; do

        show_menu  # display the menu

        # Read the user's menu choice
        read -p "  Enter your choice [1-5]: " CHOICE
        echo ""

        # 'case' is like a switch statement — matches the choice to a function
        case "$CHOICE" in
            1)
                identify_file_type
                ;;
            2)
                display_file_info
                ;;
            3)
                extract_strings
                ;;
            4)
                # Reset the remembered file so user can enter a new one
                echo ""
                echo -e "${CYAN}${BOLD}━━━  CHANGE LOADED FILE  ━━━${RESET}"
                echo ""
                CURRENT_FILE=""  # clear the memory
                ask_for_new_file
                ;;
            5)
                echo -e "${GREEN}${BOLD}  Thank you for using the File Analysis Tool. Goodbye!${RESET}"
                echo ""
                exit 0  # exit with code 0 = success
                ;;
            *)
                # Any other input that doesn't match 1-5
                echo -e "${RED}  [ERROR] Invalid choice. Please enter a number between 1 and 5.${RESET}"
                ;;
        esac

        # After each feature runs, pause so the user can read the output
        echo ""
        echo -e "${YELLOW}  Press [Enter] to return to the main menu...${RESET}"
        read -rs  # -r = raw input, -s = silent (hides arrow key garbage like ^[[B)

    done
}

# ============================================================
#  ENTRY POINT
#  This line at the bottom calls the main function to start
# ============================================================
main
