public class ThreadDemo {

    static class MyThread extends Thread {
        private String name;

        MyThread(String name) {
            this.name = name;
        }

        public void run() {
            for (int i = 1; i <= 5; i++) {
                System.out.println(name + " - Count " + i);
                try {
                    Thread.sleep(5000);
                } catch (Exception e) {}
            }
        }
    }

    public static void main(String[] args) throws Exception {
        MyThread t1 = new MyThread("Alpha");
        MyThread t2 = new MyThread("Beta");
        MyThread t3 = new MyThread("Gamma");

        t1.start();
        t2.start();
        t3.start();

        t1.join();
        t2.join();
        t3.join();

        System.out.println("All threads finished.");
    }
}
