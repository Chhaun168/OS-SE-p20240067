public class RunnableDemo {

    static class Task implements Runnable {
        private String name;

        Task(String name) {
            this.name = name;
        }

        public void run() {
            for (int i = 1; i <= 3; i++) {
                System.out.println(name + " step " + i);
                try {
                    Thread.sleep(300);
                } catch (Exception e) {}
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Thread t1 = new Thread(new Task("Download"));
        Thread t2 = new Thread(new Task("Process"));
        Thread t3 = new Thread(new Task("Upload"));

        t1.start();
        t2.start();
        t3.start();

        t1.join();
        t2.join();
        t3.join();

        System.out.println("All tasks done.");
    }
}
