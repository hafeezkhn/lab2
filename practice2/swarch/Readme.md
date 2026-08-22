
# C++ Architecture & Design Cheatsheet

A full reference covering modern C++, design patterns, synchronization, IPC, embedded system use cases, and advanced system design topics.

---

<details>
<summary>Design and Architecture Models to Study</summary>

<details>
<summary>🎯 Software Architecture Models</summary>

* Layered Architecture
* Hexagonal (Ports and Adapters)
* Clean Architecture (Onion)
* Microkernel (Plug-in Architecture)
* Reactive Systems (Actor Model)
* Publisher-Subscriber Systems
* Event-driven Architectures
* CQRS (Command Query Responsibility Segregation)

</details>

<details>
<summary>🎯 Embedded Systems Models</summary>

* Control-Loop Model (Periodic Sampling)
* Real-Time Finite State Machine (FSM)
* Task Scheduling Models (Round-robin, RTOS)
* Event-driven Embedded Systems
* Sensor Fusion Models (Kalman Filter, Complementary Filter)

</details>
</details>

<details>
<summary>🧱 Composite Pattern & Smart Pointers</summary>

<details>
<summary>Why use <code>std::shared_ptr</code> in Composite Pattern?</summary>

* Manages lifetime of components in a tree-like structure.
* Allows shared ownership of nodes, enabling reuse.

</details>

<details>
<summary>When should <code>std::weak_ptr</code> be used?</summary>

* To avoid cyclic references (e.g., child holding a back-reference to parent).

</details>

<details>
<summary>Can <code>unique_ptr</code> be used in Composite Pattern?</summary>

* Yes, if ownership is strictly hierarchical and components are not shared.

</details>

<details>
<summary>Best Practice</summary>

* Use <code>unique_ptr</code> where possible.
* Use <code>shared_ptr</code> with <code>weak_ptr</code> to handle shared and non-owning relationships.

</details>
</details>

<details>
<summary>❓ Conceptual Q&A</summary>

<details>
<summary>🔁 Why not use <code>lock()</code> and <code>unlock()</code> directly in C++?</summary>

**Answer**: Prefer RAII like <code>std::lock_guard</code> or <code>std::unique_lock</code> to avoid deadlocks and make code exception-safe.

</details>

<details>
<summary>🔄 Composite Pattern and Smart Pointers</summary>

* <code>shared_ptr</code>: automatic memory management.
* <code>weak_ptr</code>: break ownership cycles.
* <code>unique_ptr</code>: strict ownership.
* Smart pointers embody RAII.

</details>

<details>
<summary>Smart Pointer Impact on Copy/Assignment</summary>

* <code>shared_ptr</code>: shared ownership.
* <code>unique_ptr</code>: move-only semantics.

</details>

<details>
<summary>Which Design Patterns Leverage Smart Pointers?</summary>

* Composite, Observer, Factory, Decorator.

</details>

<details>
<summary>What is RAII and why is it critical?</summary>

* Resource Acquisition Is Initialization: resources (locks, memory, files) are acquired and released by objects' lifetime, ensuring exception safety and no leaks.

</details>

<details>
<summary>How does Dependency Inversion relate to testability?</summary>

* High-level modules depend on abstractions, making components easily mockable during testing.

</details>

<details>
<summary>Why prefer interfaces over inheritance?</summary>

* Interfaces promote composition over inheritance, reducing tight coupling and supporting better modularity.

</details>

<details>
<summary>Difference between Observer and Callback?</summary>

* Observer: multiple subscribers notified via publisher.
* Callback: single function called when event occurs.

</details>

<details>
<summary>When to choose Strategy vs State pattern?</summary>

* Strategy: interchangeable algorithms at runtime.
* State: object changes behavior as its internal state changes.

</details>

<details>
<summary>Factory vs Abstract Factory?</summary>

* Factory: creates one product.
* Abstract Factory: creates families of related products.

</details>
</details>

<details>
<summary>⚙️ Advanced Modern C++ Concepts</summary>

* Move Semantics (<code>std::move</code>, <code>&&</code>)
* Lambda Expressions, <code>std::function</code>
* RAII for safety
* <code>constexpr</code>, <code>noexcept</code>, <code>decltype</code>, <code>auto</code>
* Ranges/Views (C++20)
* Coroutines (C++20)
* Concepts (C++20)
* Modules (C++20)

</details>

<details>
<summary>🏛️ SOLID Principles</summary>

| Principle             | Description                                 |
| --------------------- | ------------------------------------------- |
| Single Responsibility | Each class does one thing                   |
| Open/Closed           | Open for extension, closed for modification |
| Liskov Substitution   | Subtypes replace base types                 |
| Interface Segregation | Small, specific interfaces                  |
| Dependency Inversion  | Depend on abstractions                      |

</details>

<details>
<summary>Design Patterns Summary</summary>

| Type       | Patterns                                     |
| ---------- | -------------------------------------------- |
| Creational | Factory, Builder, Singleton                  |
| Structural | Composite, Adapter, Decorator, Proxy         |
| Behavioral | Observer, Strategy, Command, State, Mediator |

**Additional Patterns to Study**:

* Visitor
* Chain of Responsibility
* Flyweight
* Prototype
* Bridge

</details>

<details>
<summary>🔗 IPC Mechanisms</summary>

<details>
<summary>UNIX Domain & TCP Sockets</summary>

* <code>send()</code>, <code>recv()</code>, client-server communication.

</details>

<details>
<summary>Named Pipes (FIFOs)</summary>

* Persistent file-based IPC.

</details>

<details>
<summary>Shared Memory (<code>mmap</code>, <code>shmget</code>)</summary>

* Fast, zero-copy memory sharing.

</details>

<details>
<summary>Message Queues</summary>

* POSIX, SysV queues.

</details>

<details>
<summary>Signals & Semaphores</summary>

* Lightweight signaling mechanisms.

</details>
</details>

<details>
<summary>🌐 Inter-Node Communication</summary>

| Mechanism      | Use Case                            |
| -------------- | ----------------------------------- |
| TCP/IP Sockets | Peer-to-peer communication          |
| gRPC           | Remote procedure calls              |
| ZeroMQ         | Lightweight pub-sub messaging       |
| DDS            | Real-time pub-sub for robotics/ADAS |
| MQTT           | IoT lightweight messaging           |
| REST           | Web service communication           |

**Important Topics**:

* Serialization: Protobuf, JSON, FlatBuffers
* Secure channels: TLS, mTLS
* Heartbeats, retries, and QoS for distributed systems

</details>

<details>
<summary>🕹️ Synchronization Models</summary>

<details>
<summary>1️⃣ Wait-and-Send (Condition Variable)</summary>

```cpp
std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;

void producer() {
    std::lock_guard<std::mutex> lock(mtx);
    data_ready = true;
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return data_ready; });
}
````

</details>

<details>
<summary>2️⃣ Callback (Asynchronous Event)</summary>

```cpp
void onDataReceived(const std::string& data) {
    std::cout << "Received: " << data << std::endl;
}

void asyncReceive(std::function<void(std::string)> callback) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    callback("Sensor Data");
}

int main() {
    asyncReceive(onDataReceived);
}
```

</details>

<details>
<summary>Summary Table</summary>

| Feature     | Wait-and-Send      | Callback      |
| ----------- | ------------------ | ------------- |
| Blocking    | Yes                | No            |
| Trigger     | Condition Met      | Event Occurs  |
| Usage       | Thread Sync        | Event Systems |
| Complexity  | Lower              | Higher        |
| Performance | CPU Waste Possible | CPU Efficient |

</details>
</details>




