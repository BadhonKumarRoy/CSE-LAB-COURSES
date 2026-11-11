#!/bin/bash

# Linux File Analysis and Inspection Tool
# Features: File Type, Permissions, Strings, Hash, Pattern Search

# --- Colors ---
RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
BOLD='\033[1m'
RESET='\033[0m'

# Remembers the last loaded file across all menu options
CURRENT_FILE=""

# --- show_menu: Draws the main menu ---
show_menu() {
    clear
    echo -e "${CYAN}${BOLD}"
    echo "  ╔══════════════════════════════════════════════╗"
    echo "  ║    Linux File Analysis & Inspection Tool     ║"
    echo "  ╠══════════════════════════════════════════════╣"
    echo "  ║                                              ║"
    echo "  ║   1.  Identify File Type                     ║"
    echo "  ║   2.  Display File Info & Permissions        ║"
    echo "  ║   3.  Extract Readable Strings               ║"
    echo "  ║   4.  Calculate Hash                         ║"
    echo "  ║   5.  Search Text Pattern                    ║"
    echo "  ║   6.  Change Loaded File                     ║"
    echo "  ║   7.  Exit                                   ║"
    echo "  ║                                              ║"
    echo "  ╚══════════════════════════════════════════════╝"
    echo -e "${RESET}"
    if [[ -n "$CURRENT_FILE" ]]; then
        echo -e "  ${BOLD}Loaded File :${RESET} ${GREEN}$CURRENT_FILE${RESET}"
    else
        echo -e "  ${BOLD}Loaded File :${RESET} ${YELLOW}None  (you will be asked when you pick option 1-5)${RESET}"
    fi
    echo ""
}

# --- ask_for_new_file: Prompts user to enter a file path ---
ask_for_new_file() {
    echo -e "  ${BOLD}Hint — You are currently in:${RESET} ${CYAN}$(pwd)${RESET}"
    echo -e "  ${BOLD}Hint — Full path example  :${RESET} ${CYAN}/home/kali/Desktop/myfile.txt${RESET}"
    echo ""
    echo -e "${YELLOW}  Enter the full path to the file:${RESET}"
    read -rp "  > " FILEPATH

    if [[ -z "$FILEPATH" ]]; then
        echo -e "${RED}  [ERROR] No file path entered.${RESET}"; return 1
    fi
    if [[ ! -f "$FILEPATH" ]]; then
        echo -e "${RED}  [ERROR] File not found: $FILEPATH${RESET}"
        echo -e "  ${YELLOW}Tip: Make sure you typed the full path correctly.${RESET}"; return 1
    fi

    CURRENT_FILE="$FILEPATH"
    echo -e "  ${GREEN}✔ File loaded and remembered!${RESET}"
    echo ""
}

# --- get_filename: Reuses loaded file or asks for a new one ---
get_filename() {
    if [[ -n "$CURRENT_FILE" ]]; then
        echo -e "  ${BOLD}Currently loaded file:${RESET}"
        echo -e "  ${GREEN}→ $CURRENT_FILE${RESET}"
        echo ""
        echo -e "  ${YELLOW}Use this file? [Press Enter = Yes  |  N = Change file]:${RESET}"
        read -rp "  > " REUSE
        echo ""
        if [[ "$REUSE" =~ ^[Nn]$ ]]; then
            ask_for_new_file || return 1
        else
            FILEPATH="$CURRENT_FILE"
        fi
    else
        ask_for_new_file || return 1
    fi
}

# --- identify_file_type: Uses 'file' command ---
identify_file_type() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  IDENTIFY FILE TYPE  ━━━${RESET}"
    echo ""
    get_filename || return
    echo ""
    echo -e "${GREEN}[+] Running: file \"$FILEPATH\"${RESET}"
    echo ""
    echo -e "${BOLD}  File Type:${RESET}"
    file "$FILEPATH"
    echo ""
    echo -e "${BOLD}  MIME Type:${RESET}"
    file -b --mime-type "$FILEPATH"
    echo ""
    echo -e "${BOLD}  Character Encoding:${RESET}"
    file -b --mime-encoding "$FILEPATH"
    echo ""
}

# --- display_file_info: Uses 'ls' and 'stat' ---
display_file_info() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  FILE INFO & PERMISSIONS  ━━━${RESET}"
    echo ""
    get_filename || return
    echo ""

    echo -e "${GREEN}[+] Running: ls -lh \"$FILEPATH\"${RESET}"
    echo ""
    echo -e "${BOLD}  Permissions & Ownership:${RESET}"
    ls -lh "$FILEPATH"
    echo ""

    PERMS=$(ls -l "$FILEPATH" | awk '{print $1}')
    echo -e "  ${BOLD}Permission String Breakdown: ${YELLOW}$PERMS${RESET}"
    echo ""
    printf "  %-16s %s\n" "Position  1   :" "File type         ( - = regular file,  d = directory )"
    printf "  %-16s %s\n" "Positions 2-4 :" "Owner permissions ( r = read,  w = write,  x = execute )"
    printf "  %-16s %s\n" "Positions 5-7 :" "Group permissions ( r = read,  w = write,  x = execute )"
    printf "  %-16s %s\n" "Positions 8-10:" "Others permission ( r = read,  w = write,  x = execute )"
    echo ""

    echo -e "${GREEN}[+] Running: stat \"$FILEPATH\"${RESET}"
    echo ""
    echo -e "${BOLD}  Detailed File Statistics:${RESET}"
    echo "  ──────────────────────────────────────────────────────────────────"
    printf "  %-18s %-30s %s\n" "File:"             "$(stat -c '%n' "$FILEPATH")"       "<- name of the file"
    printf "  %-18s %-30s %s\n" "Size:"             "$(stat -c '%s' "$FILEPATH") bytes"  "<- actual content size in bytes"
    printf "  %-18s %-30s %s\n" "Blocks Used:"      "$(stat -c '%b' "$FILEPATH")"       "<- disk blocks allocated"
    printf "  %-18s %-30s %s\n" "IO Block:"         "$(stat -c '%B' "$FILEPATH") bytes"  "<- size of each block Linux reads at once"
    printf "  %-18s %-30s %s\n" "File Type:"        "$(stat -c '%F' "$FILEPATH")"       "<- regular file, directory, symlink, etc."
    printf "  %-18s %-30s %s\n" "Inode:"            "$(stat -c '%i' "$FILEPATH")"       "<- Linux's internal unique ID for this file"
    printf "  %-18s %-30s %s\n" "Hard Links:"       "$(stat -c '%h' "$FILEPATH")"       "<- how many names point to this file"
    echo "  ──────────────────────────────────────────────────────────────────"
    printf "  %-18s %-30s %s\n" "Last Accessed:"    "$(stat -c '%x' "$FILEPATH")"       "<- last time the file was opened/read"
    printf "  %-18s %-30s %s\n" "Last Modified:"    "$(stat -c '%y' "$FILEPATH")"       "<- last time the file content was changed"
    printf "  %-18s %-30s %s\n" "Last Changed:"     "$(stat -c '%z' "$FILEPATH")"       "<- last time permissions or metadata changed"
    printf "  %-18s %-30s %s\n" "Created (Birth):"  "$(stat -c '%w' "$FILEPATH")"       "<- when the file was first created"
    echo "  ──────────────────────────────────────────────────────────────────"
    echo ""
}

# --- extract_strings: Uses 'strings' command ---
extract_strings() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  EXTRACT READABLE STRINGS  ━━━${RESET}"
    echo ""
    get_filename || return
    echo ""

    echo -e "${YELLOW}Enter minimum string length to extract (default is 4):${RESET}"
    read -p "  > " MIN_LEN
    [[ -z "$MIN_LEN" ]] && MIN_LEN=4

    if ! [[ "$MIN_LEN" =~ ^[0-9]+$ ]]; then
        echo -e "${RED}[ERROR] Please enter a valid number.${RESET}"; return
    fi

    echo ""
    echo -e "${GREEN}[+] Running: strings -n $MIN_LEN \"$FILEPATH\"${RESET}"
    echo ""
    STRING_COUNT=$(strings -n "$MIN_LEN" "$FILEPATH" | wc -l | xargs)
    echo -e "${BOLD}  Total readable strings found: ${YELLOW}$STRING_COUNT${RESET}"
    echo ""

    echo "  How would you like to view the strings?"
    printf "  %-4s %s\n" "a." "Show all strings (scrollable)"
    printf "  %-4s %s\n" "b." "Show first 20 strings only"
    printf "  %-4s %s\n" "c." "Search within strings"
    read -p "  Choice [a/b/c]: " VIEW_CHOICE
    echo ""
    echo -e "${BOLD}  Extracted Strings:${RESET}"
    echo "  ─────────────────────────────────────"

    case "$VIEW_CHOICE" in
        a|A) strings -n "$MIN_LEN" "$FILEPATH" | less ;;
        b|B)
            strings -n "$MIN_LEN" "$FILEPATH" | head -20
            echo -e "\n  ${YELLOW}(Showing first 20 of $STRING_COUNT strings)${RESET}"
            ;;
        c|C)
            echo -e "${YELLOW}  Enter keyword to search for inside strings:${RESET}"
            read -p "  > " KEYWORD
            [[ -z "$KEYWORD" ]] && { echo -e "${RED}  [ERROR] No keyword entered.${RESET}"; return; }
            strings -n "$MIN_LEN" "$FILEPATH" | grep -i --color=always "$KEYWORD"
            [[ ${PIPESTATUS[1]} -ne 0 ]] && echo -e "${RED}  No matches found for: \"$KEYWORD\"${RESET}"
            ;;
        *) strings -n "$MIN_LEN" "$FILEPATH" | head -20 ;;
    esac
    echo ""
}

# --- calculate_hash: SHA-256, MD5, SHA-1 ---
calculate_hash() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  CALCULATE HASH  ━━━${RESET}"
    echo ""
    get_filename || return
    echo ""
    echo -e "${BOLD}  A hash is a unique fingerprint of a file."
    echo -e "  If even one byte changes, the hash changes completely.${RESET}"
    echo ""
    echo "  ──────────────────────────────────────────────────"
    echo -e "${GREEN}[+] SHA-256${RESET} (most secure, widely used)"
    sha256sum "$FILEPATH"
    echo ""
    echo -e "${GREEN}[+] MD5${RESET}    (fast but weaker — still common for checksums)"
    md5sum "$FILEPATH"
    echo ""
    echo -e "${GREEN}[+] SHA-1${RESET}  (older, being phased out)"
    sha1sum "$FILEPATH"
    echo "  ──────────────────────────────────────────────────"
    echo ""
}

# --- search_pattern: Uses 'grep' with 4 modes ---
search_pattern() {
    echo ""
    echo -e "${CYAN}${BOLD}━━━  SEARCH TEXT PATTERN  ━━━${RESET}"
    echo ""
    get_filename || return
    echo ""

    echo -e "${YELLOW}  Enter keyword or pattern to search:${RESET}"
    read -rp "  > " KEYWORD
    [[ -z "$KEYWORD" ]] && { echo -e "${RED}  [ERROR] No keyword entered.${RESET}"; return; }

    echo ""
    echo "  Search mode:"
    printf "  %-4s %s\n" "a." "Normal (case-sensitive)"
    printf "  %-4s %s\n" "b." "Case-insensitive"
    printf "  %-4s %s\n" "c." "Show line numbers"
    printf "  %-4s %s\n" "d." "Count matching lines only"
    read -rp "  Choice [a/b/c/d]: " MODE
    echo ""

    echo -e "${GREEN}[+] Searching for: \"$KEYWORD\" in $FILEPATH${RESET}"
    echo "  ──────────────────────────────────────────────────"

    case "$MODE" in
        a|A) grep --color=always "$KEYWORD" "$FILEPATH" ;;
        b|B) grep -i --color=always "$KEYWORD" "$FILEPATH" ;;
        c|C) grep -n --color=always "$KEYWORD" "$FILEPATH" ;;
        d|D) echo -e "  Matching lines found: ${YELLOW}$(grep -c "$KEYWORD" "$FILEPATH")${RESET}" ;;
        *)   grep --color=always "$KEYWORD" "$FILEPATH" ;;
    esac

    [[ $? -ne 0 && "$MODE" != "d" && "$MODE" != "D" ]] && \
        echo -e "${RED}  No matches found for: \"$KEYWORD\"${RESET}"

    echo "  ──────────────────────────────────────────────────"
    echo ""
}

# --- Main loop ---
main() {
    echo -e "${CYAN}${BOLD}"
    echo "  ┌─────────────────────────────────────────────────┐"
    echo "  │  Welcome to the Linux File Analysis Tool  v1.0  │"
    echo "  │  Built with Bash | Linux Programming Lab        │"
    echo "  └─────────────────────────────────────────────────┘"
    echo -e "${RESET}"
    sleep 1

    while true; do
        show_menu
        read -p "  Enter your choice [1-7]: " CHOICE
        echo ""

        case "$CHOICE" in
            1) identify_file_type ;;
            2) display_file_info ;;
            3) extract_strings ;;
            4) calculate_hash ;;
            5) search_pattern ;;
            6)
                echo -e "${CYAN}${BOLD}━━━  CHANGE LOADED FILE  ━━━${RESET}"
                echo ""
                CURRENT_FILE=""
                ask_for_new_file
                ;;
            7)
                echo -e "${GREEN}${BOLD}  Thank you for using the File Analysis Tool. Goodbye!${RESET}"
                echo ""; exit 0
                ;;
            *)
                echo -e "${RED}  [ERROR] Invalid choice. Enter a number between 1 and 7.${RESET}"
                ;;
        esac

        echo ""
        echo -e "${YELLOW}  Press [Enter] to return to the main menu...${RESET}"
        read -rs
    done
}

main
