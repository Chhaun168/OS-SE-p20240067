import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class PoolDemo {

    static class Task implements Runnable {
        int id;

        Task(int id) {
            this.id = id;
        }

        public void run() {
            System.out.println("Task " + id + " running on " + Thread.currentThread().getName());
            try {
                Thread.sleep(1000);
            } catch (Exception e) {}
        }
    }

    public static void main(String[] args) {
        ExecutorService pool = Executors.newFixedThreadPool(2);

        for (int i = 1; i <= 6; i++) {
            pool.execute(new Task(i));
        }

        pool.shutdown();
    }
}
