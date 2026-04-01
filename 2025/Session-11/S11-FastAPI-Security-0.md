# Policy Based Access Control Tutorial with Python, Casbin, and FastAPI

Created using Copilot

Let’s break down **RBAC**, **PBAC**, and **ABAC** in a way that’s easy to understand, even if you're just starting out
with access control concepts. Then I’ll show you a simple Python example to help make it clearer.

---

## 🛡️ What Are RBAC, PBAC, and ABAC?

Imagine you’re in a school, and there are different rooms: a **library**, a **science lab**, and a **teachers’ lounge**.
Not everyone can go everywhere — access depends on **who you are**, **what you’re doing**, or **what you’re allowed to
do**.

![rbac-pbac-abac-comparison.webp](../assets/rbac-pbac-abac-comparison.webp)

### 1. **RBAC – Role-Based Access Control**

**Think of roles like job titles.**

- If you're a **student**, you can enter the **library**.
- If you're a **teacher**, you can enter the **teachers’ lounge**.
- If you're a **lab assistant**, you can enter the **science lab**.

🔑 **Access is based on your role.**

#### ✅ Pros:

- Easy to manage.
- Good for organizations with clear roles.

#### ❌ Cons:

- Not flexible — if someone needs temporary access, you have to change their role.
- Doesn’t consider context (like time of day or task).

---

### 2. **PBAC – Policy-Based Access Control**

**Think of policies like rules written by the school.**

- A policy might say: *“Only students with a science project can enter the lab.”*
- Or: *“Teachers can access the lounge during school hours.”*

🔑 **Access is based on rules (policies) that consider roles, actions, and sometimes context.**

#### ✅ Pros:

- More flexible than RBAC.
- Easier to manage complex access needs.

#### ❌ Cons:

- Can get complicated with too many policies.
- Requires a good system to manage and evaluate policies.

---

### 3. **ABAC – Attribute-Based Access Control**

**Think of attributes like personal details or conditions.**

- Attributes could be: your **age**, **grade**, **project type**, **time of day**, etc.
- A rule might say: *“Anyone with a valid ID and a science project can enter the lab between 9am–5pm.”*

🔑 **Access is based on multiple attributes — not just roles.**

#### ✅ Pros:

- Super flexible.
- Great for dynamic environments.

#### ❌ Cons:

- Complex to set up and maintain.
- Harder to audit who has access and why.

---

## 🐍 Python Code Example

Let’s simulate a simple access control system using all three methods.

```python
# Sample user data
user = {
    "name": "Alice",
    "role": "student",
    "attributes": {
        "has_project": True,
        "project_type": "science",
        "time": "14:00"
    }
}


# RBAC: Role-Based Access Control
def rbac_access(user, resource):
    role_permissions = {
        "student": ["library"],
        "teacher": ["teachers_lounge"],
        "lab_assistant": ["science_lab"]
    }
    return resource in role_permissions.get(user["role"], [])


# PBAC: Policy-Based Access Control
def pbac_access(user, resource):
    policies = {
        "science_lab": lambda u: u["role"] == "student" and u["attributes"]["has_project"],
        "teachers_lounge": lambda u: u["role"] == "teacher",
    }
    policy = policies.get(resource)
    return policy(user) if policy else False


# ABAC: Attribute-Based Access Control
def abac_access(user, resource):
    if resource == "science_lab":
        return (
                user["attributes"]["project_type"] == "science" and
                "09:00" <= user["attributes"]["time"] <= "17:00"
        )
    return False


# Test access
resource = "science_lab"
print("RBAC Access:", rbac_access(user, resource))  # False
print("PBAC Access:", pbac_access(user, resource))  # True
print("ABAC Access:", abac_access(user, resource))  # True
```

---

Let’s look at how **RBAC**, **PBAC**, and **ABAC** could be used in a **real app or website**, like a school management
system, an online learning platform, or even a company intranet.

---

## 🎓 Example: School Management Web App

Imagine a web app used by students, teachers, and administrators. It has features like:

- Viewing grades
- Uploading assignments
- Managing student records
- Accessing private staff documents

Here’s how each access control model could be applied:

---

### 🔐 RBAC in a Real App

**Use Case**: Assign access based on user roles.

- **Student** role: Can view their own grades and submit assignments.
- **Teacher** role: Can view and grade student submissions.
- **Admin** role: Can manage users and access all data.

**Implementation**:

- When a user logs in, their role is checked.
- The app shows or hides features based on that role.

**Pros**: Simple to implement with role checks.
**Cons**: Not flexible for temporary or conditional access.

---

### 📜 PBAC in a Real App

**Use Case**: Define policies like:

- “Teachers can only edit grades during the grading period.”
- “Students can only submit assignments before the deadline.”

**Implementation**:

- Policies are written as rules in code or a policy engine.
- The app checks these rules before allowing actions.

**Pros**: More control over when and how access is granted.
**Cons**: Requires a policy engine or custom logic.

---

### 🧬 ABAC in a Real App

**Use Case**: Use attributes like:

- User’s grade level
- Assignment type
- Time of day
- Device used

**Example Rule**: “Students in Year 12 can access exam prep materials between 8am–6pm from school devices.”

**Implementation**:

- Attributes are collected (user info, time, device).
- Access is granted if all conditions match.

**Pros**: Very flexible and dynamic.
**Cons**: Complex to manage and audit.

---

## 🧪 Sample Python Logic for a Web App

Here’s how you might use these models in a Flask-like web app:

```python
def can_access(user, resource, action):
    # RBAC
    if user.role == "admin":
        return True

    # PBAC
    if resource == "grades" and action == "edit":
        return user.role == "teacher" and is_grading_period()

    # ABAC
    if resource == "exam_prep":
        return (
                user.attributes["grade_level"] == 12 and
                "08:00" <= current_time() <= "18:00" and
                user.attributes["device"] == "school_device"
        )

    return False
```

---

## 🧠 Summary

| Model    | Based On   | Flexibility | Complexity | Example                               | Real App Use                                  | Best For          | Tools                |
|----------|------------|-------------|------------|---------------------------------------|-----------------------------------------------|-------------------|----------------------|
| **RBAC** | Roles      | Low         | Simple     | Student can access library            | Role-based menus and permissions              | Simple apps       | Role tables          |
| **PBAC** | Policies   | Medium      | Moderate   | Students with projects can access lab | Time-based or task-based access               | Medium complexity | Policy engines       |
| **ABAC** | Attributes | High        | Complex    | Access based on project type and time | Context-aware access (device, time, location) | Advanced apps     | Attribute evaluators |

---



