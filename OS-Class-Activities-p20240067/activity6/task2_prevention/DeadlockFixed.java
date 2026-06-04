import java.util.concurrent.Semaphore;

class Account {
    String name;
    int balance;

    Account(String name, int balance) {
        this.name = name;
        this.balance = balance;
    }
}

class Transfer {

    static Semaphore mutex = new Semaphore(1);

    static void transfer(Account from,
                         Account to,
                         int amount) {

        try {

            mutex.acquire();

            System.out.println(Thread.currentThread().getName()
                    + " entered critical section");

            Thread.sleep(1000);

            from.balance -= amount;
            to.balance += amount;

            System.out.println(
                    Thread.currentThread().getName()
                    + " transferred "
                    + amount
                    + " from "
                    + from.name
                    + " to "
                    + to.name);

        } catch (InterruptedException e) {

            e.printStackTrace();

        } finally {

            mutex.release();

        }
    }
}

public class DeadlockFixed {

    public static void main(String[] args)
            throws Exception {

        Account accountA =
                new Account("Account-A", 1000);

        Account accountB =
                new Account("Account-B", 1000);

        int startingTotal =
                accountA.balance + accountB.balance;

        System.out.println(
                "Starting total: "
                + startingTotal);

        Thread t1 =
                new Thread(
                        () -> Transfer.transfer(
                                accountA,
                                accountB,
                                100),
                        "Worker-1");

        Thread t2 =
                new Thread(
                        () -> Transfer.transfer(
                                accountB,
                                accountA,
                                200),
                        "Worker-2");

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        int finalTotal =
                accountA.balance + accountB.balance;

        System.out.println();
        System.out.println(
                "Final A: "
                + accountA.balance);

        System.out.println(
                "Final B: "
                + accountB.balance);

        System.out.println(
                "Final total: "
                + finalTotal);

        System.out.println(
                "No deadlock occurred");
    }
}
