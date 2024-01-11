use libesedb::EseDb;

fn main() {
    let filename = std::env::args()
        .nth(1)
        .expect("specify path to .esedb file");
    let db = EseDb::open(&filename).unwrap();
    println!("Database Overview ({}):", filename);
    for table in db.iter_tables().unwrap() {
        let table = table.unwrap();
        println!(
            "  {} [{:?}]",
            table.name().unwrap(),
            table
                .iter_columns()
                .unwrap()
                .map(|c| c.unwrap().name().unwrap())
                .collect::<Vec<String>>()
                .join(", "),
        );
        for record in table.iter_records().unwrap() {
            let record = record.unwrap();
            for i in 0..record.count_values().unwrap() {
                println!(
                    "  ├ T={:?} L={}, M={} V={:?}",
                    table.column(i).unwrap().variant().unwrap(),
                    record.is_long(i).unwrap(),
                    record.is_multi(i).unwrap(),
                    record.value(i).unwrap(),
                );
            }
        }
    }
}
