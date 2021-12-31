package com.codewithmosh.executors;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;

public class ExecutorsDemo {
  public static void show() {
    var executor = Executors.newFixedThreadPool(2);

    try {
      var future = executor.submit(() -> {
        LongTask.simulate();
        return 1;
      });

      System.out.println("Do more work");

      try {
        var result = future.get();
        System.out.println(result);
      } catch (InterruptedException | ExecutionException e) {
        e.printStackTrace();
      }
    }
    finally {
      executor.shutdown();
    }
  }
}
