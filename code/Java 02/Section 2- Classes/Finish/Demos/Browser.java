package com.codewithmosh;

public class Browser {
  // only navigate is public
  public void navigate(String address) {
    String ip = findIpAddress(address);
    String html = sendHttpRequest(ip);
    System.out.println(html);
  }

  // hide from other classes, only used internally
  private String sendHttpRequest(String ip) {
    return "<html></html>";
  }

  // hide from other classes, only used internally
  private String findIpAddress(String address) {
    return "127.0.0.1";
  }
}
