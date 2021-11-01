# Pessimistic Offline Lock 

We used Pessimistic Offline Lock to solve concurrency issues.

To follow Bell's principle of designing for simplicity, we have made a loose account login permission: multiple users can log into the same account. As people with qualifications to log in to the same account have similar tasks and are likely to perform similar operations or modify the same group of objects, the probability of conflicts is relatively high.

The optimistic lock may costs less when an App does not expect many conflicts. However, one need to pay higher prices if a collision does occur because all pending changes need to be aborted.

With that high conflict assumption in mind, we think that when users editing data, targeted records should be locked for exclusive use until one finishes his or her work. Therefore, Pessimstic Offline Lock may be more suitable for our application. 

Moreover, we decided to use Exclusive Write Lock because it is easy to implement and has great liveness.  

