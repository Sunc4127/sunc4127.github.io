package com.codewithmosh;

public class TextBox {

  // declare field
  // should initialize the field to avoid null pointer exception
  public String text = "";

  public void setText(String text) {
    this.text = text;
  }

  public void clear() {
    // don't need to use 'this'
    text = "";
  }
}
