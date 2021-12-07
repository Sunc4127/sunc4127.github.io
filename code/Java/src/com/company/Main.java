package com.company;

public class Main {

    public static void main(String[] args) {
        // class, member (field, method), member (method)
        System.out.println("Start");
        printNumbers(4);
        System.out.println("End");
    }

    public static void printNumbers(int limit) {
        for (int i = 0; i < limit; i += 2) {
            System.out.println(i);
        }
    }
}
