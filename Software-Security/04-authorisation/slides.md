---
theme: nmt
background: https://cover.sli.dev
title: Authorisation & PyCasbin
class: text-left
drawings:
  persist: false
transition: fade
mdc: true
duration: 90min
---

# Authorisation & PyCasbin


<div @click="$slidev.nav.next" class="mt-12 -mx-4 p-4" hover:bg="white op-10">
<p>Press <kbd>Space</kbd> or <kbd>RIGHT</kbd> for next slide/step <fa7-solid-arrow-right /></p>
</div>

<div class="abs-br m-6 text-xl">
  <a href="https://github.com/adygcode/SaaS-FED-Notes" target="_blank" class="slidev-icon-btn">
    <fa7-brands-github class="text-zinc-300 text-3xl -mr-2"/>
  </a>
</div>


<!--
The last comment block of each slide will be treated as slide notes. It will be visible and editable in Presenter Mode along with the slide. [Read more in the docs](https://sli.dev/guide/syntax.html#notes)
-->


---
layout: default
level: 2
---

# Navigating Slides

Hover over the bottom-left corner to see the navigation's controls panel.

## Keyboard Shortcuts

|                                                     |                             |
|-----------------------------------------------------|-----------------------------|
| <kbd>right</kbd> / <kbd>space</kbd>                 | next animation or slide     |
| <kbd>left</kbd>  / <kbd>shift</kbd><kbd>space</kbd> | previous animation or slide |
| <kbd>up</kbd>                                       | previous slide              |
| <kbd>down</kbd>                                     | next slide                  |

---
layout: section
---

# Objectives

---
level: 2
layout: two-cols
---

# Objectives

::left::



::right::



---
level: 2
layout: figure-side
figureUrl: public/orly-book-cover-dashboards.png
---

# Contents

<Toc minDepth="1" maxDepth="1" columns="2" />

---
layout: section
---

# 🌟 Ice Breaker

- Who decides **who can do what** in a system?
- Name an app with different user privileges.

<!-- Presenter Notes:
Use student examples like LMS or banking apps.
-->

---
layout: section
---

# What is Authorisation

---
level: 2
---

# What is Authorisation

- Controls what an authenticated user can do
- Happens *after* authentication
- Enforced by backend logic

<!-- Presenter Notes:
Authn vs Authz distinction.
-->

---
layout: section
---

# What are RBAC, ABAC, PBAC et al

---
level: 2
---

# What are RBAC, ABAC, PBAC et al


## Access Control Models
- **RBAC**: roles with permissions
- **ABAC**: attributes-based rules
- **PBAC**: policy-driven rules

<!-- Presenter Notes:
Focus on RBAC for this unit.
-->


---
layout: section
---
# Core Access Control Models
## RBAC, ABAC & PBAC

<!-- Presenter Notes:
This section summarises the three most important models students
are expected to recognise and compare.
-->

---
## RBAC — Role-Based Access Control

**What it is:**
- Access is granted based on **roles**
- Roles group permissions together

**How it works:**
- Users → roles
- Roles → permissions

**Examples:**
- Admin, staff, student roles
- Enterprise business systems

✅ Simple and easy to manage  
✅ Scales well  
❌ Limited flexibility for complex rules

<!-- Presenter Notes:
Reinforce that RBAC is the most common model students will encounter.
-->

---
## ABAC — Attribute-Based Access Control

**What it is:**
- Access decisions based on **attributes**

**Common attributes:**
- User (department, clearance)
- Resource (owner, sensitivity)
- Environment (time, location)

**Examples:**
- Cloud platforms
- Fine-grained data protection

✅ Very flexible  
✅ Context-aware decisions  
❌ More complex to design and manage

<!-- Presenter Notes:
Emphasise that ABAC evaluates conditions dynamically at runtime.
-->

---
## PBAC — Policy-Based Access Control

**What it is:**
- Access governed by **policies**
- Policies define rules independently of code

**How it works:**
- Requests evaluated against policies
- Often implemented via policy engines

**Examples:**
- Enterprise security platforms
- Compliance-driven systems

✅ Centralised control  
✅ Highly configurable  
❌ Policy complexity can grow quickly

<!-- Presenter Notes:
PBAC is often seen as an architectural approach rather than a single model.
-->

---
layout: section
---
# Comparing the Core Models

---
## RBAC vs ABAC vs PBAC

| Model | Decision Based On | Flexibility | Complexity | Typical Use |
|-----|------------------|-------------|-------------|-------------|
| RBAC | Roles | Medium | Low | Enterprise apps |
| ABAC | Attributes | High | High | Cloud systems |
| PBAC | Policies | High | Medium–High | Security platforms |

<!-- Presenter Notes:
Focus students on trade-offs: simplicity vs flexibility.
-->

---
## Key Takeaways

- **RBAC** is best for clear, stable permissions
- **ABAC** handles complex, dynamic conditions
- **PBAC** provides centralised policy control
- Real systems often **combine these models**

<!-- Presenter Notes:
Link this back to Casbin’s ability to support multiple models.
-->

---
layout: section
---
# Access Control Models
## Beyond RBAC, ABAC & PBAC

<!-- Presenter Notes:
Introduce this as a broadening of student knowledge.
Explain that RBAC, ABAC and PBAC are common, but not the only models.
-->

---
## Why So Many Models?

Different systems have different needs:
- Simplicity vs flexibility
- Centralised vs user-controlled access
- Static vs dynamic environments

No single model fits all situations.

<!-- Presenter Notes:
Use the phrase “right tool for the job”.
-->

---
## ACL – Access Control Lists

**What it is:**
- Each resource lists who can access it

**How it works:**
- User → resource → permission

**Examples:**
- File permissions
- Network device rules

✅ Simple  
❌ Poor scalability

<!-- Presenter Notes:
Policies live *on the resource*, not centrally.
-->

---
## DAC – Discretionary Access Control

**What it is:**
- Owners decide who can access their resources

**Examples:**
- Operating system files
- Shared folders

✅ Flexible  
❌ Weak security guarantees

<!-- Presenter Notes:
Explain that users can accidentally over-share.
-->

---
## MAC – Mandatory Access Control

**What it is:**
- Central authority enforces labels and clearances

**Examples:**
- Military systems
- Government data systems

✅ Very secure  
❌ Rigid and hard to manage

<!-- Presenter Notes:
Stress that users cannot override permissions.
-->

---
## ReBAC – Relationship-Based Access Control

**What it is:**
- Decisions based on relationships

**Examples:**
- "Friend of"
- "Member of"
- "Owner of"

✅ Natural for social systems  
❌ Requires relationship graphs

<!-- Presenter Notes:
Good example: social media privacy.
-->

---
## TBAC – Task-Based Access Control

**What it is:**
- Permissions tied to tasks or workflows

**Examples:**
- Approval processes
- Business workflows

✅ Least privilege  
❌ Complex to implement

<!-- Presenter Notes:
Permissions exist only while the task is active.
-->

---
## RuBAC – Rule-Based Access Control

**What it is:**
- If-then rules evaluated at runtime

**Examples:**
- Network firewalls
- Policy engines

✅ Very powerful  
❌ Difficult to maintain

<!-- Presenter Notes:
Rules can become complex quickly.
-->

---
## Hybrid Access Control Models

**What it is:**
- Combining multiple models

**Typical approach:**
- RBAC for broad access
- ABAC or rules for fine-grained checks

✅ Practical and flexible  
❌ Higher complexity

<!-- Presenter Notes:
This is how most real enterprise systems work.
-->

---
layout: section
---
# Model Comparison

---
## Access Control Model Comparison

| Model | Decision Based On | Granularity | Scalability | Common Use |
|-----|------------------|-------------|--------------|------------|
| ACL | User–Resource list | Low | Poor | File systems |
| DAC | Resource owner | Low | Poor | Desktop OS |
| MAC | Security labels | Medium | Medium | Government |
| RBAC | Roles | Medium | High | Enterprise apps |
| ABAC | Attributes | High | High | Cloud systems |
| PBAC | Policies | High | High | Policy engines |
| ReBAC | Relationships | High | Medium | Social platforms |
| TBAC | Tasks | Medium | Medium | Workflows |
| RuBAC | Rules | High | Medium | Security tools |
| Hybrid | Combined models | Very High | High | Enterprise cloud |

<!-- Presenter Notes:
Don’t read the whole table aloud—highlight trends instead.
-->

---
## Key Takeaways

- RBAC is easiest to manage
- ABAC offers maximum flexibility
- Other models solve niche problems
- Hybrid models dominate real systems

<!-- Presenter Notes:
Good exam summary slide.
-->



---
layout: section
---

# What is Casbin?

- Casbin
- PyCasbin
- Policies
- Models


---
level: 2
---

# What is Casbin?

- Casbin
- PyCasbin
- Policies
- Models

- Open-source authorisation library
- Supports multiple models
- PyCasbin integrates with FastAPI

<!-- Presenter Notes:
Stress separation of policy from code.
-->


---
## Casbin Policy
```csv
p, admin, /secure/users/add, POST
p, admin, /secure/users/list, GET
p, staff, /secure/users/list, GET
g, jane, admin
g, bill, staff
```

<!-- Presenter Notes:
Walk policy line by line.
-->

---
## Casbin Model Overview
```ini
[request_definition]
r = sub, obj, act
[policy_definition]
p = sub, obj, act
[role_definition]
g = _, _
[policy_effect]
e = some(where (p.eft == allow))
[matchers]
m = (g(r.sub, p.sub) || r.sub == p.sub) && r.obj == p.obj && r.act == p.act
```

<!-- Presenter Notes:
Explain model governs decision logic.
-->


---
layout: section
---

# Implementing RBAC with PyCasbin

---
level: 2
---
## Worked Demo Flow
1. Authenticate user
2. Call Casbin enforcer
3. Evaluate model + policy
4. Allow or deny

<!-- Presenter Notes:
Walk through request lifecycle.
-->


---
level: 2
---

# Implementing RBAC with PyCasbin

TODO: Add content on Authorisation



---
## Summary
- RBAC simplifies access control
- Casbin externalises rules
- Enforcer protects endpoints

<!-- Presenter Notes:
Reinforce learning outcomes.
-->


---

# Acknowledgements & References

## References (APA 7)

Casbin. (2024). *Casbin documentation: Overview*. Apache Software Foundation. https://casbin.apache.org/docs/overview

FastAPI. (2026). *FastAPI documentation*. https://fastapi.tiangolo.com/

Sandhu, R. S., Coyne, E. J., Feinstein, H. L., & Youman, C. E. (1996). Role‑based access control models. *IEEE Computer, 29*(2), 38–47. https://doi.org/10.1109/2.485845

Ferraiolo, D. F., Kuhn, D. R., & Chandramouli, R. (2007). *Role‑based access control* (2nd ed.). Artech House.

Relington, J. (2025). *Role‑ and attribute‑based access control (RBAC/ABAC): Identity in cybersecurity*. Independently published.

Bellis, B., Fleury, T., & Kim, T. W. (2008). *Access control, authentication, and public key infrastructure*. Jones & Bartlett.
> - Some content was generated with the assistance of Microsoft Copilot

---
layout: end
---

# Fin!

### Authorisation Haiku

- ...
