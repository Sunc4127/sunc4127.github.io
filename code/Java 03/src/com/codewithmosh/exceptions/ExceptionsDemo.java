package com.codewithmosh.exceptions;

public class ExceptionsDemo {
  public static void show() {
    var account = new Account();
    try {
      account.withdraw(10);
    } catch (AccountException e) {
      var cause = e.getCause();
      System.out.println(cause.getMessage());
    }
  }
}
