# तत्त्व: - Tattva

<div align="center">
  <img src="assets/तत्त्व.png" alt="तत्त्व: logo" width="200">

  <h1>तत्त्व: - Tattva</h1>

  <p>A tiny language project born from a developer getting frustrated with modern web frameworks.</p>

  <img src="https://api.memegen.link/images/stonks/_/A_language_of_my_own.png" alt="Stonks: A language of my own" width="300">

  <p><em>(Yes, even the documentation is built in तत्त्व:.)</em></p>
</div>


## Why तत्त्व:?

<div align="center">
  <img src="https://api.memegen.link/images/gru/Learn_a_framework/Learn_another_framework/Build_my_own_language/Become_the_framework.png" alt="Gru’s Plan: learn a framework, learn another framework, build my own language, become the framework" width="250">
</div>

---

Well, React JS and the growing family of hooks, prop drilling, and frequent library updates started to feel like a lot to keep up with. You pick up a library, get comfortable with it, and a few months later, boom! Something has changed.

I wanted a simpler way to build websites for my own use, so I started thinking about a language where elements are first-class building blocks.

I wanted something inspired by the object-oriented paradigm, with simple state tracking and a way to build interfaces without depending on an ever-growing collection of libraries.

The idea eventually became **तत्त्व:**.

I picked the Sanskrit name because the language is built around the fundamental elements of a page: elements, state, and views.

## What makes it special?

<div align="center">
  <img src="https://api.memegen.link/images/drake/Just_use_Svelte/Keep_building_Tattva_because_I_promised_a_friend.png" alt="Drake meme: just use Svelte versus keep building Tattva because I promised a friend" width="250">
</div>

---

Honestly, nothing much.

While building तत्त्व:, I discovered Svelte, which was already pretty close to the kind of experience I had in mind.

I kept going anyway, partly because the idea was fun and partly because I had already promised a friend that I would finish this project.

तत्त्व: is a work in progress. I am learning as I build it, experimenting with ideas, and figuring out the design along the way.

## How I built it

<div align="center">
  <img src="https://api.memegen.link/images/db/Me/Writing_normal_JavaScript/Building_a_language.png" alt="Distracted Boyfriend: writing normal JavaScript versus building a programming language in C++" width="250">
</div>

---

Initially, I wanted to make something that would make everyone look at the screen and say, "Bro, wow!"

Then I searched around and realised that making an entire programming language is quite an undertaking.

The first practical plan I came up with was:

1. Design the syntax.
2. Parse the source code.
3. Translate it into reactive vanilla JavaScript.

That is still the basic shape of the project.

I started learning about parsing, and the compiler now uses a handwritten lexer and a recursive-descent parser.

I also spent time understanding visitor patterns and Pratt parsing, partly thanks to the excellent [Crafting Interpreters](https://craftinginterpreters.com/) book. The current expression parser is recursive descent.

I started writing everything by hand, but eventually hit the wall. I was getting tired of writing repetitive code.

So I brought in my best AI friends and became the orchestrator, a bit like Sergio Busquets directing play from midfield.

I describe the idea, let AI help draft the implementation, and then inspect, understand, and verify the generated code.

<div align="center">
  <img src="https://api.memegen.link/images/stonks/AI_writes_the_boilerplate/I_review_it_and_become_the_orchestrator.png" alt="Stonks: AI writes the boilerplate, I review it and become the orchestrator" width="300">
</div>


## A little about the design

<div align="center">
  <img src="https://api.memegen.link/images/chair/Put_everything_in_one_global_state_table/That_should_be_simple/Multiple_instances_need_local_state/Now_they_are_sharing_state/So_each_instance_gets_its_own_local_table/Finally_separate_registries.png" alt="American Chopper argument meme about state architecture" width="280">
</div>

---

My first design idea was to put everything into one global state table.

That fell apart pretty quickly when multiple copies of the same element needed to maintain separate state.

I had to rethink the architecture:

- **Global state table:** Values shared across the application.
- **Local state table and registry:** Maintained separately for each rendered element or component instance.

The generated runtime gives reactive nodes unique IDs and registers the values they depend on.

Local nodes register themselves inside their own component.

When a global value changes, the runtime can find the registered nodes that depend on it and refresh them.

Local updates use their own maps, allowing two instances of the same element to maintain completely separate state.

This is the current prototype architecture.

There are still some known gaps, including:

- Nested list and map updates.
- Stable element identity.
- Lifecycle management.
- Updates that span component boundaries.

A lot of the runtime design is still evolving.

## What can you do in तत्त्व: right now?

<div align="center">
  <img src="https://api.memegen.link/images/tried/Syntax_support_exists/Runtime_is_another_story.png" alt="At least you tried meme" width="300">
</div>

---

The compiler is written in C++.

It reads `.ttv`, `.tattva`, and `.web` files and generates:

- `index.html`
- `style.css`
- `app.js`

### The current prototype can compile

- App configuration, pages, simple layouts, and exact-path navigation.
- Elements with named parameters, fields, methods, and views.
- HTML-like tags, text, attributes, and common event handlers.
- Global values, persisted globals, and basic derived values.
- Numbers, strings, booleans, `none`, lists, maps, lambdas, and common operators.
- Conditions, loops, functions, and basic error-handling syntax.
- Raw CSS blocks and JavaScript interop blocks.
- Basic generated model CRUD helpers and record proxies.

Some features are more complete than others. Syntax support does not necessarily mean every associated runtime behaviour is finished.

## Examples

Here are ten small projects that demonstrate what you can build with the current compiler.

Each example has its own source file and screenshot. They are also available as separate routes in the [Documentation Site](https://aaklon.github.io/Tattva/).

| Example         | Source                                               |                                           Preview                                            |
| :-------------- | :--------------------------------------------------- | :------------------------------------------------------------------------------------------: |
| Navbar          | [Source](documentation/sources/navbar.tattva)        |        <img src="documentation/previews/navbar.png" alt="Navbar example" width="300">        |
| Form            | [Source](documentation/sources/form.tattva)          |          <img src="documentation/previews/form.png" alt="Form example" width="300">          |
| Search bar      | [Source](documentation/sources/search-bar.tattva)    |    <img src="documentation/previews/search-bar.png" alt="Search bar example" width="300">    |
| Hero section    | [Source](documentation/sources/hero-section.tattva)  |  <img src="documentation/previews/hero-section.png" alt="Hero section example" width="300">  |
| Blog with votes | [Source](documentation/sources/blog-votes.tattva)    | <img src="documentation/previews/blog-votes.png" alt="Blog with votes example" width="300">  |
| Todo list       | [Source](documentation/sources/todo-list.tattva)     |     <img src="documentation/previews/todo-list.png" alt="Todo list example" width="300">     |
| Profile card    | [Source](documentation/sources/profile-card.tattva)  |  <img src="documentation/previews/profile-card.png" alt="Profile card example" width="300">  |
| Pricing cards   | [Source](documentation/sources/pricing-cards.tattva) | <img src="documentation/previews/pricing-cards.png" alt="Pricing cards example" width="300"> |
| Dashboard       | [Source](documentation/sources/dashboard.tattva)     |     <img src="documentation/previews/dashboard.png" alt="Dashboard example" width="300">     |
| FAQ accordion   | [Source](documentation/sources/faq.tattva)           |           <img src="documentation/previews/faq.png" alt="FAQ example" width="300">           |

The [Documentation Site](https://aaklon.github.io/Tattva/) combines the guide and all ten examples into one Tattva project.

Each example route includes its corresponding source code.

The documentation site source is available at [`documentation/documentation.tattva`](documentation/documentation.tattva).

## How to compile your code

You need a C++17-compatible compiler such as `g++` or `clang++`.

### 1. Build the compiler

From the repository root:

```sh
make build
```

### 2. Compile your Tattva project

Pass the source folder and output folder as arguments:

```sh
./parser path/to/source path/to/output
```

For example, to compile the guide and all examples together:

```sh
./parser documentation documentation/dist
```

The compiler reads supported source files directly inside the input folder. It does not search nested folders.

The output folder contains:

```text
index.html
style.css
app.js
```

### Alternatively, use the Makefile

```sh
make compile DIR=documentation OUT=documentation/dist
```

## Documentation

<div align="center">
  <img src="https://api.memegen.link/images/gb/Write_documentation/Build_a_documentation_site/Build_it_in_Tattva/Use_it_to_learn_Tattva.png" alt="Expanding Brain: write documentation, build a documentation site, build it in Tattva, use it to learn Tattva" width="250">
</div>

---


The documentation is itself written in तत्त्व:.

Start with the [Documentation](https://aaklon.github.io/Tattva/). It includes beginner lessons and ten example routes, each with its corresponding Tattva source code.

**Live preview:**

## What is coming in the future?

<div align="center">
  <img src="https://api.memegen.link/images/fine/Compiler_works._Runtime_works./Nested_updates_and_stable_identity_are_on_fire.png" alt="This Is Fine: compiler and runtime work, but nested updates and stable identity are on fire" width="250">
</div>

The goal is to turn this prototype into a much more complete language.

There are still plenty of difficult compiler and runtime decisions ahead. I am also lazy enough to make no promises about the timeline.

Here are some things I would like to work towards:

- **Reactivity:** Reliable updates for fields, globals, derived values, and nested lists, maps, and records.
- **Components:** Stable element instances, lifecycle behaviour, and working default and named slots.
- **Views:** Complete view behaviour, including forms, two-way binding, references, keyed loops, and safe attributes.
- **Routing:** Route patterns, route parameters, query values, wildcard pages, and persistent layouts.
- **Models:** Typed model fields, validation, CRUD operations, and browser storage.
- **Asynchronous operations:** Async functions, `await`, network helpers, timers, and timer cleanup.
- **Error handling:** Clear compiler errors for syntax, names, scope, routes, models, and invalid view composition.
- **Developer experience:** A local server, automatic reloads, formatting, source maps, and browser compilation.

Fingers crossed I ship a few of these.

## Want to contribute?

You absolutely can.

Clear bug reports, small fixes, examples, and thoughtful design discussions are welcome.

This is a learning project, and contributions are a great way to help shape what it becomes.

## License

तत्त्व: is available under the [MIT License](LICENSE).
