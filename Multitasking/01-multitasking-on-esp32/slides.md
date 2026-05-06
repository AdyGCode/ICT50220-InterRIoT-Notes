---
theme: nmt
background: https://cover.sli.dev
title: ESP32 and Multitasking
class: text-left
drawings:
  persist: false
transition: fade
mdc: true
duration: 90min
---

# ESP32 Multitasking
## An Introduction

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
level: 2
---

# Contents

<Toc minDepth="1" maxDepth="1" columns="2" />

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

# Warm up!

---
layout: two-cols
level: 2
---

# Warm‑Up 

# TO DO

---
layout: section
---

# Objectives

---
level: 2
layout: figure-side
figureUrl: ./public/images/orly-book-cover-security-next-month.jpg
---

# Objectives

By the end of this session, learners will be able to:

- Explain what *application security* is and what it is not

- Describe why applications are a primary security target

- Identify business, user, and organisational impacts of insecure applications

- Explain why security must be embedded throughout development

<!-- Presenter Notes:
Set expectations clearly. This session is about motivation and context, not implementation detail.
-->

---
layout: section
---

Add race condition and mutex diagrams
🧮 Add FreeRTOS priority inversion example

---
layout: section
---

# Checklist

---
level: 2
---

# Checklist

- [ ] Applications are the primary modern attack surface
- [ ] Application security is a development responsibility
- [ ] Security failures affect real people
- [ ] Security must be built in, not bolted on


---
layout: section
---

# Out of Class Activities

---
level: 2
---

# Out of Class Activities

Investigate these two references.

Ensure you understand the SDLC and the top 10 security risks.

- **OWASP Top 10 – Overview**  
  https://owasp.org/www-project-top-ten/

- **Microsoft Secure Development Lifecycle**  
  https://learn.microsoft.com/security/engineering/sdl

<!-- Presenter Notes:
Do not assign these now unless needed. 
They are reference pillars for the entire unit.
-->



---
layout: section
---

# Acknowledgements & References

---
level: 2
---

# Acknowledgements & References


- Anderson, R. (2020). *Security engineering: A guide to building dependable distributed systems* (3rd ed.). Wiley.

- McGraw, G. (2018). *Software security: Building security in*. Addison‑Wesley.

- Microsoft. (2023). *Secure development lifecycle*.  https://learn.microsoft.com/security/engineering/sdl

- Open Web Application Security Project. (2023). *OWASP Top 10: 2021*.  https://owasp.org/www-project-top-ten/

- Saltzer, J. H., & Schroeder, M. D. (1975). The protection of information in computer systems. *Proceedings of the IEEE, 63*(9), 1278–1308. https://doi.org/10.1109/PROC.1975.9939



> Some content may have been generated with the assistance of Microsoft Copilot


---
layout: end
---

# FIN!


<Announcement type="brainstorm" class="text-3xl mt-8 ">
<p class="text-white!">Autumn data flows</p>  
<p class="pt-2 text-white!">Quiet locks guard passing leaves</p>  
<p class="pt-2 text-white!">Trust rests in strong code</p>
</Announcement>

<!-- Presenter Notes:
Read aloud. Pause briefly.
This reinforces reflection rather than technical recall.
-->



