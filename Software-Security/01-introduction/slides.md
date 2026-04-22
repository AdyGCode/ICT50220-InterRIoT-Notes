---
theme: nmt
background: https://cover.sli.dev
title: Application Security - Introduction
class: text-left
drawings:
  persist: false
transition: fade
mdc: true
duration: 90min
---

# Application Security - Introduction


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
level: 2
---

# Contents

<Toc minDepth="1" maxDepth="1" columns="2" />

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
figureUrl: public/orly-book-cover-security-next-month.jpg
---

---
layout: section
---

# 🌟 Ice Breaker

## TODO: Add ice-breaker



---
layout: section
---

# Application Security:<br>Purpose & Context

---
level: 2
layout: two-cols
---

# Application Security: Purpose and Context
## Why application security matters

::left::

Application security refers to:
- processes,
- techniques, and 
- controls.

These are used to protect software applications from threats throughout their lifecycle. 

::right::

Application security focuses on the:
- logic, 
- data handling, and 
- execution behaviour.

---
level: 2
layout: two-cols
---

# Application Security: Purpose and Context
## Why application security matters (2)

::left::

Modern applications are:
- Exposed to the internet
- Highly interconnected
- Responsible for sensitive data
- Continuously updated and deployed

::right::

As a result, vulnerabilities in applications are one of the most common and damaging causes of security incidents.


---
level: 2
---

# Application Security: Purpose and Context
## Why application security matters (3)

<Youtube id="7U-RbOKanYs" width="60%" height="60%" />

https://www.youtube.com/watch?v=7U-RbOKanYs

---
level: 2
---


# Application Security: Purpose and Context
## Why application security matters 4)

### Tutorials

- OWASP Top 10 Overview: https://owasp.org/www-project-top-ten/
- Secure Software Development Lifecycle (Microsoft): https://learn.microsoft.com/security/engineering/sdl

---
level: 2
layout: two-cols
---


# Application Security: Purpose and Context
## Why application security matters (5)

<br>

### Exercise: Identifying Security Impact

::left::

### Research

Identify a real-world application breach...

Examples include, but should be different from:

- Equifax
- Optus

::right::

#### Questions

- What type of application was affected?
- What data was compromised?
- What was the business/user impact?

Discuss...

<!-- Presenter Notes:

**Expected Outcomes**
- Students can articulate why application security is critical.
- Students identify consequences beyond “technical failure”.



**Presenter Guidance**
Encourage learners to think beyond hacking and consider:
- Legal consequences
- Loss of trust
- Operational disruption

Use this slide to establish relevance. 
Emphasise that application security failures usually 
come from design or coding decisions, not advanced hacking tools. 

Connect content to apps students use daily.


Introduce why application security is essential in modern software development.

Protect confidentiality, integrity, and availability (CIA triad)
Prevent unauthorised access to data and system resources
Reduce organisational risk, legal exposure, and reputational damage
Meet organisational policies, industry standards, and compliance requirements
Build secure-by-design software rather than relying on post-deployment fixes

-->


---
layout: section
---
# Application Security: Key Terms and Concepts

---
level: 2
---

# Application Security: Key Terms and Concepts

A shared vocabulary is essential for secure software development. 

### Key concepts
- Threat, vulnerability, exploit
- Least privilege
- Defence in depth
- Attack surface
- Authentication vs authorisation
- Confidentiality, Integrity, Availability (CIA)

---
level: 2
---

# Application Security: Key Terms and Concepts

<Youtube id="sdpxddDzXfE" width="60%" height="60%" />

https://www.youtube.com/watch?v=sdpxddDzXfE

---
level: 2
---

# Application Security: Key Terms and Concepts

### Additional Learning/References

- Cybersecurity Terminology (IBM): https://www.ibm.com/topics/cybersecurity
- NIST Glossary: https://csrc.nist.gov/glossary

---
level: 2
layout: two-cols
---

# Application Security: Key Terms and Concepts

## Exercise: Australian References

::left::

### Identify

Identify Resources within, and relevant to **Australia** for Application Security terms and concepts.

::right::

### Contribute

Use the Teams Group chat **Loop** to add your resources.
   - No Duplication!
   - Use MybIB to create full APA v6/v7 References
   - If no Author, replace with company, or group
   - Ensure date is correct (if it says 8 years ago, year must be 2018)


---
level: 2
layout: two-cols
---

# Application Security: Key Terms and Concepts
## Exercise: Threat Modelling Basics

::left::

### Preparation

Locate a diagram showing a simple web login process.

Investigate and understand the process shown.

::right::

### Identify

- One threat
- One vulnerability
- One possible exploit

<!-- Presenter Notes:

**Expected Outcomes**
- Clear distinction between threat, vulnerability, and exploit.
- Improved security reasoning.

**Presenter Guidance**
Correct misconceptions early, especially confusing vulnerabilities with attacks.


Spend extra time clarifying authentication vs authorisation. This misunderstanding is extremely common and leads directly to broken access control issues in real applications.


   Core Security Concepts

Application security
Threat, vulnerability, exploit
Attack surface
Least privilege
Defence in depth
Secure by design / secure coding
Authentication vs authorisation
Confidentiality, Integrity, Availability (CIA)

Access and Execution

Code access security (CAS)
Permissions and roles
Protected resources
Sandboxing

Data Protection

Encryption / decryption
Symmetric vs asymmetric cryptography
Hashing
Key management
-->

---
layout: section
---

# Application Security: Key Knowledge Areas

---
level: 2
---

# Application Security: Key Knowledge Areas

## What developers should know

- Secure coding principles
- Object-oriented design and encapsulation
- Cryptographic algorithms (AES, RSA, SHA)
- Secure input/output handling
- Error handling and logging

...


---
layout: section
---

# Acknowledgements & References

---
level: 2
---

# Acknowledgements & References


- TODO: Add references etc


> Some content may have been generated with the assistance of Microsoft Copilot


---
layout: end
---

# FIN!




