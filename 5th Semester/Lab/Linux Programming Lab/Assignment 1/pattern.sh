#!/bin/bash

while true
do
    echo
    echo "===== Pattern Generator ====="
    echo "1. Increasing Triangle"
    echo "2. Decreasing Triangle"
    echo "3. Pyramid"
    echo "4. Number Triangle"
    echo "5. Exit"

    echo -n "Choose an option: "
    read choice

    if (( choice == 5 ))
    then
        echo "Exiting program..."
        break
    fi

    if (( choice < 1 || choice > 5 ))
    then
        echo "Invalid choice!"
        continue
    fi

    echo -n "Enter number of rows: "
    read n

    case $choice in

        1)
            for (( i=1; i<=n; i++ ))
            do
                for (( j=1; j<=i; j++ ))
                do
                    echo -n "* "
                done
                echo
            done
            ;;

        2)
            for (( i=n; i>=1; i-- ))
            do
                for (( j=1; j<=i; j++ ))
                do
                    echo -n "* "
                done
                echo
            done
            ;;

        3)
            for (( i=1; i<=n; i++ ))
            do
                for (( s=1; s<=n-i; s++ ))
                do
                    echo -n " "
                done

                for (( j=1; j<=i; j++ ))
                do
                    echo -n "* "
                done

                echo
            done
            ;;

        4)
            for (( i=1; i<=n; i++ ))
            do
                for (( j=1; j<=i; j++ ))
                do
                    echo -n "$j "
                done
                echo
            done
            ;;

    esac
done